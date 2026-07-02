/* =========================
   HANDLE TRANSACTION STATE
========================= */

function handleTransactionMessage(message) {
  switch (message.type) {
    /* =========================
            WAIT SENDER
        ========================= */

    case "transaction_wait_sender":
      renderTransactionStatus("WAITING SENDER", "Please tap your NFC card.");

      break;

    /* =========================
            WAIT RECEIVER
        ========================= */

    case "transaction_wait_receiver":
      renderTransactionStatus(
        "WAITING RECEIVER",
        "Please tap receiver NFC card.",
      );

      break;

    /* =========================
            PROCESSING
        ========================= */

    case "transaction_processing":
      renderTransactionStatus("PROCESSING", "Processing transaction...");

      break;

    /* =========================
            SUCCESS
        ========================= */

    case "transaction_success":
        renderTransactionStatus("SUCCESS", "Money transferred successfully.");
        setTimeout(() => {
            resetTransferForm();
        }, 1200);
    break;

    /* =========================
            FAILED
        ========================= */

    case "transaction_failed":
      renderTransactionStatus("FAILED", "Transaction failed.");

        setTimeout(() => {
            resetTransferForm();
        }, 1200);
    break;

    /* =========================
            BUSY
        ========================= */

    case "transaction_busy":
      renderTransactionStatus("BUSY", "Another transaction is running.");

      setTimeout(() => {
            resetTransferForm();
        }, 1200);

      break;
  }
}
