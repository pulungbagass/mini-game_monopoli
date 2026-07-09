#include "transaction_executor.h"

#include "../data/transaction_session.h"

#include "../services/transaction_service.h"
#include "../services/property_transaction_service.h"
#include "../services/transaction_session_service.h"

#include "../websocket/handlers/ws_broadcast.h"
#include "../websocket/handlers/ws_transaction.h"
#include "../websocket/handlers/ws_transaction_broadcast.h"


/* ======================================================
   Execute Transaction
====================================================== */

bool executeTransaction()
{
    if (!transactionSession.active)
        return false;
    if (!transactionSession.sourceVerified)
        return false;
    if (!transactionSession.targetVerified)
        return false;
    bool success = processTransaction();

    if (success)
    {
        Serial.println();
        Serial.println("TRANSACTION SUCCESS");
        sendTransactionState(
            "transaction_success"
        );
        sendTransactionSuccess();
        broadcastGameState();
    }
    else
    {
        Serial.println();
        Serial.println("TRANSACTION FAILED");
        sendTransactionState(
            "transaction_failed"
        );
        sendTransactionFailed();
    }

    finishTransaction();
    return success;
}