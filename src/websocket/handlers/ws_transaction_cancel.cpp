#include "ws_transaction_cancel.h"

#include "../../services/transaction_session_service.h"
#include "ws_transaction.h"

/* ======================================================
   CANCEL TRANSACTION
====================================================== */

void handleTransactionCancel(
    AsyncWebSocketClient *client,
    JsonDocument &doc
)
{
    if (!isTransactionActive())
        return;

    cancelTransaction();

    sendTransactionTimeout();

    Serial.println();
    Serial.println("TRANSACTION CANCELLED BY USER");
}