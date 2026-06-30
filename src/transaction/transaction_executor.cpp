#include "transaction_executor.h"

#include "../data/transaction_session.h"
#include "../services/transaction_service.h"
#include "../services/transaction_session_service.h"
#include "../websocket/handlers/ws_broadcast.h"
#include "../websocket/handlers/ws_transaction.h"

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

    bool success = transferMoney(
        transactionSession.sourceRole,
        transactionSession.targetRole,
        transactionSession.amount
    );

    if(success)
    {
        Serial.println();
        Serial.println("TRANSACTION SUCCESS");

        sendTransactionSuccess();

        broadcastGameState();
    }
    else
    {
        Serial.println();
        Serial.println("TRANSACTION FAILED");

        sendTransactionFailed();
    }

    clearTransactionSession();

    return true;
}