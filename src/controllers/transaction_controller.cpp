#include "transaction_controller.h"

#include "../data/transaction_session.h"
#include "../services/transaction_session_service.h"
#include "../websocket/handlers/ws_transaction.h"

/* ======================================================
   UPDATE TRANSACTION
====================================================== */

void updateTransaction()
{
    if (!transactionSession.active)
        return;

    unsigned long now = millis();

    if (now - transactionSession.startTime >= 60000)
    {
        Serial.println();
        Serial.println("TRANSACTION TIMEOUT");

        sendTransactionTimeout();

        finishTransaction();
    }
}