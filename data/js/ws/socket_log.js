/* ======================================================
   GAME LOG (GLOBAL_LOG) - client state
   Disimpan urut kronologis (paling lama duluan); tiap
   halaman yang menampilkan log membalik urutan sendiri
   supaya event terbaru tampil paling atas.
====================================================== */

window.appState.gameLog = [];

const GAME_LOG_CLIENT_MAX = 300;

function handleGameLogState(data) {
  window.appState.gameLog = (data.entries || []).slice(
    -GAME_LOG_CLIENT_MAX,
  );
  refreshLogPagesIfVisible();
}

function handleGameLogEntry(data) {
  window.appState.gameLog.push({
    timestamp: data.timestamp,
    category: data.category,
    message: data.message,
    roleA: data.roleA,
    roleB: data.roleB,
  });

  if (window.appState.gameLog.length > GAME_LOG_CLIENT_MAX) {
    window.appState.gameLog.shift();
  }

  refreshLogPagesIfVisible();
}

function refreshLogPagesIfVisible() {
  if (typeof renderGameLogListIfVisible === "function") {
    renderGameLogListIfVisible();
  }
  if (typeof renderHistoryListIfVisible === "function") {
    renderHistoryListIfVisible();
  }
  if (typeof renderTransactionLogListIfVisible === "function") {
    renderTransactionLogListIfVisible();
  }
}

/* ======================================================
   HELPER: kategori -> label & warna css
====================================================== */

function gameLogCategoryMeta(category) {
  switch (category) {
    case "money_in":
      return { label: "UANG MASUK", cls: "log-money-in" };
    case "money_out":
      return { label: "UANG KELUAR", cls: "log-money-out" };
    case "property":
      return { label: "PROPERTI", cls: "log-property" };
    case "auction":
      return { label: "LELANG", cls: "log-auction" };
    case "card":
      return { label: "KARTU", cls: "log-card" };
    default:
      return { label: "INFO", cls: "log-info" };
  }
}

function formatLogTime(timestampMs) {
  // timestamp dari ESP32 adalah millis() sejak boot, bukan
  // epoch time asli (device tidak selalu punya RTC/NTP).
  // Ditampilkan sebagai durasi "sejak boot" supaya tetap
  // informatif tanpa berpura-pura ini jam dinding asli.
  const totalSeconds = Math.floor(timestampMs / 1000);
  const h = String(Math.floor(totalSeconds / 3600)).padStart(2, "0");
  const m = String(Math.floor((totalSeconds % 3600) / 60)).padStart(2, "0");
  const s = String(totalSeconds % 60).padStart(2, "0");
  return `${h}:${m}:${s}`;
}
