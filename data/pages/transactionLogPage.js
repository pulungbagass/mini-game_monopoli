/* ======================================================
   BANK: TRANSACTION LOG
   Rekaman seluruh perputaran uang (transfer, sewa, lelang,
   kartu CC/Chance yang melibatkan uang).
====================================================== */

function renderTransactionLogPage() {
  setTimeout(renderTransactionLogList, 0);
  return `
    <button class="back-button">
      ← BACK
    </button>

    <div class="page-card">
      <h2>📜 TRANSACTION LOG</h2>
      <p>Seluruh perputaran uang dalam permainan.</p>

      <div id="transactionLogTerminal" class="log-terminal">
        <p class="property-loading">Loading log...</p>
      </div>
    </div>
  `;
}
registerPage("transactionLog", renderTransactionLogPage);

function renderTransactionLogListIfVisible() {
  if (document.getElementById("transactionLogTerminal")) {
    renderTransactionLogList();
  }
}

const TRANSACTION_LOG_CATEGORIES = ["money_in", "money_out", "auction"];

function renderTransactionLogList() {
  const container = document.getElementById("transactionLogTerminal");
  if (!container) return;

  const entries = (window.appState.gameLog || []).filter((e) =>
    TRANSACTION_LOG_CATEGORIES.includes(e.category),
  );

  if (entries.length === 0) {
    container.innerHTML = `<p class="property-loading">Belum ada transaksi.</p>`;
    return;
  }

  container.innerHTML = entries
    .slice()
    .reverse()
    .map((entry) => {
      const meta = gameLogCategoryMeta(entry.category);
      return `
        <div class="log-line ${meta.cls}">
          <span class="log-time">${formatLogTime(entry.timestamp)}</span>
          <span class="log-tag">${meta.label}</span>
          <span class="log-message">${entry.message}</span>
        </div>
      `;
    })
    .join("");
}
