/* =========================
   REGISTER PAGE
========================= */

registerPage("transferPage", renderTransferPage);

/* =========================
   RENDER
========================= */

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

      <div
        id="transferContent"
        style="margin-top:20px;"
      ></div>

      <div class="transfer-form">

        <label>FROM</label>

        <input
          id="transferFrom"
          class="transfer-input"
          type="text"
          readonly
        >

        <label>TO</label>

        <select
          id="transferTo"
          class="transfer-input"
        ></select>

        <label>AMOUNT</label>

        <input
          id="transferAmount"
          class="transfer-input"
          type="number"
          inputmode="numeric"
          min="1"
          step="1"
        >

        <button
          id="startTransferButton"
          class="transfer-button"
        >
          START TRANSFER
        </button>
        <button
            id="cancelTransferButton"
            class="transfer-button transfer-cancel"
            style="display:none;"
        >
            CANCEL
        </button>

      </div>

      

    </div>
  `;
}
