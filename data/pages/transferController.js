/* =========================
   INIT TRANSFER PAGE
========================= */

function initTransferPage() {
  loadTransferPlayers();
  bindTransferButton();
}

/* =========================
   LOAD PLAYERS
========================= */

function loadTransferPlayers() {
  const fromCard = document.getElementById("transferFromCard");

  const to = document.getElementById("transferTo");

  const amount = document.getElementById("transferAmount");

  if (!fromCard || !to || !amount) return;

  const myRole = window.appState.activeRole;

  const me = getPlayer(myRole);

  if (!me) return;

  fromCard.innerHTML = `
        <strong>${me.name}</strong>
        <br>
        Balance : $${me.money}
    `;

  amount.placeholder = `Maximum : $${me.money}`;
  amount.max = me.money;
  amount.min = 1;

  to.innerHTML = "";

  window.appState.gameState.forEach((player) => {
    if (player.role === "BANK") return;

    if (player.role === myRole) return;

    const option = document.createElement("option");

    option.value = player.role;
    option.textContent = player.name;

    to.appendChild(option);
  });
}

/* =========================
   BUTTON
========================= */

function bindTransferButton() {
  const button = document.getElementById("startTransferButton");

  if (!button) return;

  button.onclick = startTransfer;
}

/* =========================
   START
========================= */

/* =========================
   START TRANSFER
========================= */

function startTransfer() {
  const me = getPlayer(window.appState.activeRole);

  if (!me) {
    alert("Player not found.");
    return;
  }

  const to = document.getElementById("transferTo").value;

  const amount = Number(document.getElementById("transferAmount").value);

  /* =========================
       VALIDATION
    ========================= */

  if (!to) {
    alert("Please select receiver.");
    return;
  }

  if (amount <= 0) {
    alert("Invalid amount.");
    return;
  }

  if (amount > me.money) {
    alert("Insufficient balance.");
    return;
  }

  /* =========================
       SEND
    ========================= */

  window.appState.socket.send(
    JSON.stringify({
      type: "start_transaction",
      toRole: to,
      amount: amount,
    }),
  );

  renderTransactionStatus("WAITING SENDER", "Tap sender NFC card.");
}

/* =========================
   TRANSACTION STATUS
========================= */

function renderTransactionStatus(title, message) {
  const content = document.getElementById("transferContent");
  if (!content) return;
  content.innerHTML = `
        <div class="page-card">
            <h3>${title}</h3>
            <br>
            <p>${message}</p>
        </div>
    `;
}

amount.addEventListener("input", () => {
  let value = Number(amount.value);

  if (value > me.money) {
    amount.value = me.money;
  }

  if (value < 1) {
    amount.value = "";
  }
});
