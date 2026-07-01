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
  }

  if (data.type === "transaction_wait_sender") {
    renderTransactionStatus(
      "STEP 1 / 2",

      "Tap Sender NFC Card",
    );
  }
  if (data.type === "transaction_wait_receiver") {
    renderTransactionStatus(
      "STEP 2 / 2",

      "Tap Receiver NFC Card",
    );
  }
  if (data.type === "transaction_processing") {
    renderTransactionStatus(
      "PROCESSING",

      "Processing transaction...",
    );
  }
  if (data.type === "transaction_success") {
    renderTransactionStatus(
      "SUCCESS",

      "Money transferred successfully.",
    );
  }
  if (data.type === "transaction_failed") {
    renderTransactionStatus(
      "FAILED",

      "Transaction failed.",
    );
  }

  /* GAME STATE */

  if (data.type === "game_state") {
    handleGameState(data);
  }

  /* ACCESS GRANTED */

  if (data.type === "access_granted") {
    console.log("ACCESS GRANTED");

    window.appState.activeRole = data.role;

    openPrivatePage();
  }

  /* ACCESS DENIED */

  if (data.type === "access_denied") {
    alert("ACCESS DENIED");
  }

  /* NEED CLAIM */

  if (data.type === "need_claim") {
    alert("PLEASE TAP NFC CARD");

    claimRole(data.role);
  }
}
