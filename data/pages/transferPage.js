/* =========================
   TRANSFER PAGE
========================= */
registerPage("transferPage", renderTransferPage);

function renderTransferPage() {
  setTimeout(initTransferPage, 0);
  return `
    <button class="back-button">
    ← BACK
    </button>
    <div class="page-card">
    <h2>MONEY TRANSFER</h2>
    <p>Transfer money between players.</p>
    <div class="section-title">
        <h3>NEW TRANSACTION</h3>
    </div>
    <div class="page-card">
        <p>From</p>
        <div
            id="transferFromCard"
            class="player-dashboard-card"
        >
            Loading...
        </div>
        <br><br>
        <p>To</p>
        <select id="transferTo"></select>
        <br><br>
        <p>Amount</p>
        <input
            id="transferAmount"
            type="number"
            placeholder=""
        >
        <br><br>
        <button
        id="startTransferButton"
        class="back-button"
        >
        START TRANSFER
        </button>
    </div>
    </div>
`;
}
