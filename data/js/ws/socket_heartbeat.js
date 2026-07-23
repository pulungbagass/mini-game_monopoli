/* ======================================================
   MOBILE-PROOF NETWORK RECOVERY (Fase C)
   ------------------------------------------------------
   Mengatasi "Ghost Socket" & "Tab Freezing": saat layar HP
   mati / user pindah ke app lain (WhatsApp dll), iOS Safari
   & Android Chrome sering membekukan JS dan menggantung
   koneksi WebSocket tanpa mengirim sinyal close yang jelas.
   Begitu layar dinyalakan lagi, UI bisa mengira socket masih
   hidup padahal sebenarnya sudah mati.

   Modul ini menambahkan 2 lapis proteksi di atas socket.js
   (Fase B) TANPA mengubah logika reconnect yang sudah ada:

   1) Page Visibility API -- cek ulang readyState begitu tab
      kembali terlihat, jangan percaya begitu saja.
   2) Ping-Pong watchdog -- kalau ESP32 berhenti kirim PING
      lebih dari 10 detik, socket dianggap mati walau secara
      teknis readyState masih OPEN.

   File ini HARUS dimuat setelah js/ws/socket.js (butuh
   connectSocket, scheduleReconnect, showReconnectIndicator
   yang didefinisikan di sana).
====================================================== */

const PING_STALE_TIMEOUT_MS = 10000;          // sesuai spesifikasi: >10 detik tanpa PING = mati
const PING_WATCHDOG_CHECK_INTERVAL_MS = 2000; // resolusi pengecekan, cukup untuk ambang 10 detik

let lastPingReceivedAt = Date.now();
let pingWatchdogTimer = null;

/* ======================================================
   1) PING-PONG WATCHDOG
====================================================== */

// Dipanggil dari socket_ui.js saat pesan {"type":"ping"} masuk.
function handleServerPing() {
  lastPingReceivedAt = Date.now();

  const socket = window.appState.socket;

  if (socket && socket.readyState === WebSocket.OPEN) {
    socket.send(JSON.stringify({ type: "pong" }));
  }
}

// Dipanggil dari socket.js tiap kali koneksi baru berhasil OPEN.
function startPingWatchdog() {
  stopPingWatchdog();

  // Reset baseline supaya tidak langsung dianggap timeout
  // begitu koneksi baru saja tersambung (belum sempat dapat
  // PING pertama dari ESP32).
  lastPingReceivedAt = Date.now();

  pingWatchdogTimer = setInterval(() => {
    const idleMs = Date.now() - lastPingReceivedAt;

    if (idleMs > PING_STALE_TIMEOUT_MS) {
      console.warn(
        `Tidak ada PING dari ESP32 selama ${idleMs}ms -- socket dianggap mati, reconnect paksa.`,
      );
      forceReconnect();
    }
  }, PING_WATCHDOG_CHECK_INTERVAL_MS);
}

// Dipanggil dari socket.js tiap kali socket ditutup (baik oleh
// server, error, maupun reconnect paksa dari modul ini sendiri).
function stopPingWatchdog() {
  if (pingWatchdogTimer) {
    clearInterval(pingWatchdogTimer);
    pingWatchdogTimer = null;
  }
}

/* ======================================================
   PAKSA TUTUP & RECONNECT
   ------------------------------------------------------
   Dipakai baik oleh watchdog ping-pong maupun oleh
   pengecekan visibilitychange di bawah.
====================================================== */

function forceReconnect() {
  stopPingWatchdog();

  const socket = window.appState.socket;

  if (socket) {
    // Lepas handler lama dulu supaya onclose bawaan tidak ikut
    // menjadwalkan reconnect kedua kali (scheduleReconnect() di
    // socket.js sudah punya guard, tapi ini lebih eksplisit &
    // menghindari log ganda yang membingungkan saat debug).
    socket.onclose = null;
    socket.onerror = null;

    try {
      socket.close();
    } catch (e) {
      // Socket sudah dalam keadaan aneh (mis. CLOSING lama di
      // iOS) -- abaikan, kita reconnect dari nol di bawah.
    }
  }

  showReconnectIndicator();
  scheduleReconnect();
}

/* ======================================================
   2) PAGE VISIBILITY API -- AUTO WAKE-UP CHECK
====================================================== */

document.addEventListener("visibilitychange", () => {
  if (document.visibilityState !== "visible") return;

  console.log("Tab/layar kembali aktif -- verifikasi status WebSocket...");

  const socket = window.appState.socket;
  const isReallyOpen = !!socket && socket.readyState === WebSocket.OPEN;

  if (!isReallyOpen) {
    console.warn(
      "WebSocket TIDAK dalam keadaan OPEN saat wake-up (readyState:",
      socket ? socket.readyState : "null (belum pernah connect)",
      ") -- socket dianggap ghost, paksa tutup & reconnect.",
    );
    forceReconnect();
    return;
  }

  // readyState memang OPEN, tapi selama layar mati ESP32 bisa
  // saja sudah menendang kita karena heartbeat timeout (Ghost
  // Socket cleanup di backend). Minta sync_req sebagai jaring
  // pengaman supaya UI selalu menampilkan state yang benar-benar
  // terkini (mis. lelang yang sudah berubah selagi kita tidur).
  if (window.appState.activeRole && socket.readyState === WebSocket.OPEN) {
    socket.send(
      JSON.stringify({
        type: "sync_req",
        role: window.appState.activeRole,
      }),
    );
  }
});
