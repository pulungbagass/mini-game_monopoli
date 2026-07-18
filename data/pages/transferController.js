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
  fromInput.value = me.name;
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
  toSelect.innerHTML = "";

  // Placeholder
  const placeholder = document.createElement("option");
  placeholder.value = "";
  placeholder.textContent = "Pilih Player";
  placeholder.disabled = true;
  placeholder.selected = true;
  placeholder.hidden = true;

  toSelect.appendChild(placeholder);

  // Player List
  window.appState.gameState.forEach((player) => {
    if (player.role === myRole) return;

    const option = document.createElement("option");
    option.value = player.role;
    option.textContent = player.name;

    toSelect.appendChild(option);
  });

  console.log("Receiver Loaded :", toSelect.options.length - 1);
}
function bindTransferButton() {
  const button = document.getElementById("startTransferButton");
  if (!button) return;
  button.onclick = startTransfer;
}
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
  console.log("SEND START_TRANSACTION");
  window.appState.activeTransactionKind = "transfer";
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
    renderTransactionStatus("WAITING SENDER", "Please tap sender NFC card.");
  }
  const cancelButton = document.getElementById("cancelTransferButton");
  if (cancelButton) {
    cancelButton.style.display = "block";
  }
}
function renderTransactionStatus(title, message) {
  const t = title.toUpperCase();
  let type = "info";
  if (t.includes("SUCCESS")) type = "success";
  else if (t.includes("FAILED") || t.includes("TIMEOUT")) type = "error";
  else if (t.includes("BUSY") || t.includes("CANCEL")) type = "warning";
  showGlobalStatus(title, message, type);
}
function resetTransferForm() {
  window.appState.activeTransactionKind = null;
  hideGlobalStatus();
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
function cancelTransfer() {
  console.log("SEND CANCEL_TRANSACTION");
  window.appState.socket.send(
    JSON.stringify({
      type: "cancel_transaction",
    }),
  );
}
