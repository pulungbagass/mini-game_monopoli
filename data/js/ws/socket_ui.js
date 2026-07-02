/* =========================
   HANDLE SOCKET MESSAGE
========================= */

function handleSocketMessage(event) {
  console.log("MESSAGE : ", event.data);

  if (event.data === "CONNECTED TO ESP32") {
    return;
  }

  const data = JSON.parse(event.data);

  /* =========================
     TRANSACTION
  ========================= */

  if (data.type === "transaction_busy") {
    alert("Transaction is already running.");
    return;
  }

  if (data.type === "transaction_wait_sender") {
    renderTransactionStatus("STEP 1 / 2", "Tap Sender NFC Card");
    return;
  }

  if (data.type === "transaction_wait_target") {
    renderTransactionStatus("STEP 2 / 2", "Waiting Receiver...");
    return;
  }

  if (data.type === "transaction_wait_receiver") {
    renderTransactionStatus("STEP 2 / 2", "Tap Receiver NFC Card");
    return;
  }

  if (data.type === "transaction_processing") {
    renderTransactionStatus("PROCESSING", "Processing transaction...");
    return;
  }

  if (data.type === "transaction_success") {
    renderTransactionStatus("SUCCESS", "Money transferred successfully.");

    setTimeout(() => {
      resetTransferForm();

      renderTransactionStatus("READY", "Create a new transaction.");
    }, 2000);

    const cancelButton = document.getElementById("cancelTransferButton");

    if (cancelButton) {
      cancelButton.style.display = "none";
    }

    return;
  }

  if (data.type === "transaction_failed") {
    renderTransactionStatus("FAILED", "Transaction failed.");

    setTimeout(() => {
      resetTransferForm();

      renderTransactionStatus("READY", "Create a new transaction.");
    }, 2000);

    const cancelButton = document.getElementById("cancelTransferButton");

    if (cancelButton) {
      cancelButton.style.display = "none";
    }

    return;
  }

  if (data.type === "transaction_timeout") {
    renderTransactionStatus(
      "TIMEOUT",
      "Transaction cancelled because timeout.",
    );

    setTimeout(() => {
      resetTransferForm();

      renderTransactionStatus("READY", "Create a new transaction.");
    }, 5000);

    const cancelButton = document.getElementById("cancelTransferButton");

    if (cancelButton) {
      cancelButton.style.display = "none";
    }

    return;
  }

  /* =========================
     GAME STATE
  ========================= */

  if (data.type === "game_state") {
    handleGameState(data);
    return;
  }

  /* =========================
     ACCESS
  ========================= */

  if (data.type === "access_granted") {
    console.log("ACCESS GRANTED");

    window.appState.activeRole = data.role;

    openPrivatePage();

    return;
  }

  if (data.type === "access_denied") {
    alert("ACCESS DENIED");
    return;
  }

  /* =========================
     CLAIM
  ========================= */

  if (data.type === "need_claim") {
    alert("PLEASE TAP NFC CARD");

    claimRole(data.role);

    return;
  }

  console.warn("UNKNOWN MESSAGE :", data);
}
