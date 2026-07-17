function handleTransactionMessage(message) {
    switch (message.type) {
    case "transaction_wait_sender":
        updateTransactionUI("WAIT_SENDER");
        break;
    case "transaction_wait_receiver":
        updateTransactionUI("WAIT_RECEIVER");
        break;
    case "transaction_processing":
        updateTransactionUI("PROCESSING");
        break;
    case "transaction_success":
        updateTransactionUI("SUCCESS");
        break;
    case "transaction_busy":
        updateTransactionUI("BUSY");
        break;
    case "transaction_failed":
        updateTransactionUI("FAILED", {
        message: message.reason,
        });
        break;
    case "transaction_timeout":
        updateTransactionUI("TIMEOUT");
        break;
    case "transaction_timeout":
        updateTransactionUI("TIMEOUT");
        break;
    }
}
