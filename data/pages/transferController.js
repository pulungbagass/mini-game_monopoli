/* =========================
   INIT
========================= */

function initTransferPage() {
  console.log("========== TRANSFER ==========");
  console.log("ROLE :", window.appState.activeRole);
  console.log("GAME STATE :", window.appState.gameState);
  console.log("==============================");

  loadTransferPlayers();
  bindTransferButton();
  bindCancelButton();
  resetTransferForm();
}

/* =========================
   LOAD PLAYER
========================= */

function loadTransferPlayers() {
  const fromInput = document.getElementById("transferFrom");
  const toSelect = document.getElementById("transferTo");
  const amountInput = document.getElementById("transferAmount");

  if (!fromInput || !toSelect || !amountInput) {
    console.error("Transfer form not found");
    return;
  }

  const myRole = window.appState.activeRole;
  const me = getPlayer(myRole);

  console.log("ACTIVE PLAYER :", me);

  if (!me) {
    console.error("Player not found :", myRole);
    return;
  }

  /* =========================
     FROM
  ========================= */

  fromInput.value = me.name;

  /* =========================
     AMOUNT
  ========================= */

  amountInput.placeholder = `Your money : $${me.money}`;
  amountInput.max = me.money;
  amountInput.min = 1;

  amountInput.onkeydown = (e) => {
    if (e.key === "e" || e.key === "E" || e.key === "+" || e.key === "-") {
      e.preventDefault();
    }
  };

  amountInput.oninput = () => {
    let value = Number(amountInput.value);

    if (value > me.money) {
      amountInput.value = me.money;
    }

    if (value < 0) {
      amountInput.value = "";
    }
  };

  /* =========================
     RECEIVER
  ========================= */

  toSelect.innerHTML = "";

  window.appState.gameState.forEach((player) => {
    if (player.role === myRole) return;

    const option = document.createElement("option");

    option.value = player.role;

    option.textContent = player.name;

    toSelect.appendChild(option);
  });

  console.log("Receiver Loaded :", toSelect.options.length);
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
   START TRANSFER
========================= */

function startTransfer() {
  console.log("START BUTTON CLICKED");

  const me = getPlayer(window.appState.activeRole);

  if (!me) {
    alert("Player not found.");
    resetTransferForm();
    return;
  }

  const toRole = document.getElementById("transferTo").value;
  const amount = Number(document.getElementById("transferAmount").value);

  console.log({
    sender: me.role,
    receiver: toRole,
    amount,
  });

  /* =========================
     VALIDATION
  ========================= */

  if (!toRole) {
    alert("Please select receiver.");
    resetTransferForm();
    return;
  }

  if (Number.isNaN(amount) || amount <= 0) {
    alert("Invalid amount.");
    resetTransferForm();
    return;
  }

  if (amount > me.money) {
    alert("Insufficient balance.");
    resetTransferForm();
    return;
  }

  /* =========================
     SEND
  ========================= */

  console.log("SEND START_TRANSACTION");

  window.appState.socket.send(
    JSON.stringify({
      type: "start_transaction",
      toRole: toRole,
      amount: amount,
    }),
  );

  if (toRole === "BANK") {
    renderTransactionStatus(
      "WAITING SENDER",

      "Tap your NFC card to transfer money to BANK.",
    );
  } else {
    renderTransactionStatus(
      "WAITING SENDER",

      "Please tap sender NFC card.",
    );
  }

  const cancelButton = document.getElementById("cancelTransferButton");

  if (cancelButton) {
    cancelButton.style.display = "block";
  }
}

/* =========================
   STATUS
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

/* =========================
   RESET TRANSFER FORM
========================= */

function resetTransferForm() {
  const myRole = window.appState.activeRole;
  const me = getPlayer(myRole);
  const fromInput = document.getElementById("transferFrom");
  const toSelect = document.getElementById("transferTo");
  const amountInput = document.getElementById("transferAmount");
  const content = document.getElementById("transferContent");
  if (me && fromInput) {
    fromInput.value = me.name;
  }

  if (me && amountInput) {
    amountInput.placeholder = `Your money : $${me.money}`;

    amountInput.max = me.money;
  }
  if (toSelect) {
    toSelect.selectedIndex = 0;
  }
  if (amountInput) {
    amountInput.value = "";
  }
  if (content) {
    content.innerHTML = "";
  }
  const cancelButton = document.getElementById("cancelTransferButton");

  if (cancelButton) {
    cancelButton.style.display = "none";
  }
  console.log("TRANSFER FORM RESET");
}

function bindCancelButton() {
  const button = document.getElementById("cancelTransferButton");

  if (!button) return;

  button.onclick = cancelTransfer;
}

/* =========================
   CANCEL TRANSFER
========================= */

function cancelTransfer() {
  console.log("SEND CANCEL_TRANSACTION");

  window.appState.socket.send(
    JSON.stringify({
      type: "cancel_transaction",
    }),
  );
}
