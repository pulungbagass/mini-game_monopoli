/* =========================
   TRANSFER PAGE
========================= */

registerPage(
  "transferPage",

  function () {
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
        <select id="transferFrom"></select>
        <br><br>
        <p>To</p>
        <select id="transferTo"></select>
        <br><br>
        <p>Amount</p>
        <input
        id="transferAmount"
        type="number"
        placeholder="1000"
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
  },
);

/* =========================
   TRANSFER PAGE
========================= */

function initTransferPage() {
  const fromSelect = document.getElementById("transferFrom");
  const toSelect = document.getElementById("transferTo");

  if (!fromSelect || !toSelect) return;

  fromSelect.innerHTML = "";
  toSelect.innerHTML = "";

  window.appState.gameState.forEach((player) => {
    const option1 = document.createElement("option");
    option1.value = player.role;
    option1.textContent = player.name;

    fromSelect.appendChild(option1);

    const option2 = document.createElement("option");
    option2.value = player.role;
    option2.textContent = player.name;

    toSelect.appendChild(option2);
  });

  document
    .getElementById("startTransferButton")
    .addEventListener("click", startTransfer);
}

/* =========================
   START TRANSFER
========================= */

function startTransfer() {
  const from = document.getElementById("transferFrom").value;

  const to = document.getElementById("transferTo").value;

  const amount = Number(document.getElementById("transferAmount").value);

  console.log({
    from,
    to,
    amount,
  });
}
