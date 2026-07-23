/* ======================================================
   KONEKSI WEBSOCKET + SILENT RECONNECT
   ------------------------------------------------------
   Prinsip: putusnya WebSocket (mis. sinyal HP lemah 1-2
   detik) TIDAK BOLEH membuat pemain "terlempar" ke layar
   lain. Kita hanya menyambung ulang di belakang layar dan
   meminta ESP32 mengirim ulang snapshot state terakhir.
====================================================== */

let savedId = localStorage.getItem("deviceId");
if (!savedId) {
  savedId = "DEV-" + Math.random().toString(36).substring(2, 10);
  localStorage.setItem("deviceId", savedId);
}
window.appState.deviceId = savedId;
console.log("DEVICE ID:", savedId);

const RECONNECT_INTERVAL_MS = 1500;
let reconnectTimer = null;

function connectSocket() {
  const socket = new WebSocket(`ws://${window.location.host}/ws`);
  window.appState.socket = socket;

  socket.onopen = () => {
    console.log("WEBSOCKET CONNECTED");

    hideReconnectIndicator();

    // Fase C: mulai/reset watchdog ping-pong tiap kali koneksi
    // baru berhasil terbentuk (typeof-check biar file ini tetap
    // aman dipakai walau socket_heartbeat.js belum ikut dimuat).
    if (typeof startPingWatchdog === "function") {
      startPingWatchdog();
    }

    if (reconnectTimer) {
      clearTimeout(reconnectTimer);
      reconnectTimer = null;
    }

    socket.send(
      JSON.stringify({
        type: "register",
        deviceId: window.appState.deviceId,
      }),
    );

    // Kalau device ini sebelumnya sudah punya role aktif
    // (BANK / player_x), berarti ini reconnect di tengah
    // permainan -- minta ESP32 kirim ulang status terkini
    // (mis. lelang yang masih berjalan) supaya modal yang
    // relevan bisa langsung muncul lagi, tanpa pemain sadar
    // sempat terputus.
    if (window.appState.activeRole) {
      socket.send(
        JSON.stringify({
          type: "sync_req",
          role: window.appState.activeRole,
        }),
      );
    }
  };

  socket.onmessage = (event) => {
    handleSocketMessage(event);
  };

  socket.onclose = () => {
    console.log("WEBSOCKET CLOSED - mencoba reconnect...");

    if (typeof stopPingWatchdog === "function") {
      stopPingWatchdog();
    }

    // JANGAN reload / redirect ke halaman lain di sini.
    // UI tetap seperti apa adanya (termasuk modal lelang
    // kalau sedang terbuka), cuma indikator kecil yang muncul.
    showReconnectIndicator();
    scheduleReconnect();
  };

  socket.onerror = () => {
    // Biarkan onclose yang menangani retry -- browser akan
    // memicu close setelah error, cukup pastikan socket ditutup.
    socket.close();
  };
}

function scheduleReconnect() {
  // Cegah tumpukan banyak percobaan berjalan bersamaan;
  // pola "coba sekali, jadwalkan lagi lewat onclose kalau
  // gagal" lebih aman daripada setInterval yang bisa membuat
  // beberapa koneksi baru menumpuk kalau attempt sebelumnya
  // belum selesai.
  if (reconnectTimer) return;

  reconnectTimer = setTimeout(() => {
    reconnectTimer = null;
    console.log("Mencoba menyambungkan ulang...");
    connectSocket();
  }, RECONNECT_INTERVAL_MS);
}

function showReconnectIndicator() {
  const el = document.getElementById("reconnectIndicator");
  if (el) el.classList.remove("hidden");
}

function hideReconnectIndicator() {
  const el = document.getElementById("reconnectIndicator");
  if (el) el.classList.add("hidden");
}

connectSocket();
