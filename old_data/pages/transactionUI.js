/* =========================
   UPDATE UI
========================= */

function updateTransactionUI(state, data = {}) {
    switch (state) {
    case "WAIT_SENDER":
        renderTransactionStatus("WAITING SENDER", "Please tap your NFC card.");

        break;

    case "WAIT_RECEIVER":
        renderTransactionStatus(
        "WAITING RECEIVER",
        "Please tap receiver NFC card.",
        );

        break;

    case "PROCESSING":
        renderTransactionStatus("PROCESSING", "Processing transaction...");

        break;

    case "SUCCESS":
        renderTransactionStatus("SUCCESS", "Money transferred successfully.");

        setTimeout(resetTransferForm, 1200);

        break;

    case "FAILED": {
        let text = "Transaction failed.";

        switch (data.message) {
        case "insufficient_balance":
            text = "Your balance is not enough.";
            break;

        case "same_player":
            text = "Cannot transfer to yourself.";
            break;

        case "target_not_found":
            text = "Receiver not found.";
            break;

        case "invalid_amount":
            text = "Invalid amount.";
            break;
        }

        renderTransactionStatus("FAILED", text);

        setTimeout(resetTransferForm, 1200);

        break;
    }

    case "BUSY":
        renderTransactionStatus("BUSY", "Another transaction is running.");

        break;

    case "TIMEOUT":
        renderTransactionStatus(
        "TRANSACTION ENDED",

        "Transaction has been cancelled.",
        );

        resetTransferForm();

        break;
    }
}
