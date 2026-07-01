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
  const from = document.getElementById("transferFrom");

  const to = document.getElementById("transferTo");

  if (!from || !to) return;

  from.innerHTML = "";
  to.innerHTML = "";

  window.appState.gameState.forEach((player) => {
    if (player.role === "BANK") return;

    const optionFrom = document.createElement("option");

    optionFrom.value = player.role;
    optionFrom.textContent = player.name;

    from.appendChild(optionFrom);

    const optionTo = document.createElement("option");

    optionTo.value = player.role;
    optionTo.textContent = player.name;

    to.appendChild(optionTo);
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
  const from = document.getElementById("transferFrom").value;

  const to = document.getElementById("transferTo").value;

  const amount = Number(document.getElementById("transferAmount").value);

  /* =========================
        VALIDATION
    ========================= */

  if (from === to) {
    alert("Sender dan Receiver tidak boleh sama.");

    return;
  }

  if (amount <= 0) {
    alert("Jumlah transfer tidak valid.");

    return;
  }

  /* =========================
            SEND TO ESP32
        ========================= */

  window.appState.socket.send(
    JSON.stringify({
      type: "start_transaction",
      fromRole: from,
      toRole: to,
      amount: amount,
    }),
  );
  renderTransactionStatus("WAITING", "Please tap sender NFC card.");
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
