#include "transaction_executor.h"

#include "../data/transaction_session.h"
#include "money_transaction_executor.h"
#include "property_transaction_executor.h"

#include "../services/transaction_service.h"
#include "../services/property_transaction_service.h"
#include "../services/transaction_session_service.h"

#include "../websocket/handlers/ws_broadcast.h"
#include "../websocket/handlers/ws_transaction.h"
#include "../websocket/handlers/ws_transaction_broadcast.h"

#include "../events/game_event.h"
#include "../data/game_log.h"


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
    bool success = false;

    switch (transactionSession.type)
    {
        case TRANSACTION_TRANSFER:
        {
            success =
                executeMoneyTransaction();
            break;
        }

        case TRANSACTION_PROPERTY:
        {
            success =
                executePropertyTransaction();
            break;
        }

        case TRANSACTION_BANK:
        {
            success = false;
            break;
        }

        case TRANSACTION_AUCTION:
        {
            success = false;
            break;
        }

        case TRANSACTION_NONE:
        default:
        {
            success = false;
            break;
        }
    }

    if (success)
    {
        Serial.println();
        Serial.println("TRANSACTION SUCCESS");

        sendTransactionState(
            "transaction_success");

        sendTransactionSuccess();

        broadcastGameState();

        // GLOBAL_LOG (Phase 1 audit): transfer uang murni
        // (Player<->Player / Player<->Bank) sebelumnya tidak
        // tercatat sama sekali di log manapun.
        if (transactionSession.type == TRANSACTION_TRANSFER)
        {
            addGameLog(
                LOG_MONEY_OUT,
                transactionSession.sourceRole + " mentransfer $" +
                    String(transactionSession.amount) + " ke " +
                    transactionSession.targetRole,
                transactionSession.sourceRole,
                transactionSession.targetRole
            );
        }
    }
    else
    {
        Serial.println();
        Serial.println("TRANSACTION FAILED");

        sendTransactionState(
            "transaction_failed");

        sendTransactionFailed();
    }

    finishTransaction();

    return success;
}