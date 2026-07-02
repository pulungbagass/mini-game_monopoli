#include "transaction_handler.h"

#include "../data/transaction_session.h"
#include "transaction_executor.h"

#include "../websocket/handlers/ws_transaction.h"
#include "../websocket/handlers/ws_transaction_broadcast.h"

/* ======================================================
   HANDLE NFC TRANSACTION
====================================================== */

void handleTransactionNFC(
    const String& role,
    const String& deviceId
)
{
    switch (transactionSession.state)
    {

        /* ==========================================
           WAIT SENDER
        ========================================== */

        case TRANSACTION_WAIT_SENDER:
        {

            if (role != transactionSession.sourceRole)
            {
                Serial.println("WRONG SENDER CARD");
                return;
            }

            transactionSession.sourceVerified = true;
            transactionSession.sourceDevice = deviceId;

            transactionSession.state =
                TRANSACTION_WAIT_RECEIVER;

            Serial.println();
            Serial.println("SENDER VERIFIED");
            Serial.println("WAIT RECEIVER");

            sendTransactionWaitTarget();

            sendTransactionState(
                "transaction_wait_receiver"
            );

            break;
        }

        /* ==========================================
           WAIT RECEIVER
        ========================================== */

        case TRANSACTION_WAIT_RECEIVER:
        {

            if (role != transactionSession.targetRole)
            {
                Serial.println("WRONG RECEIVER CARD");
                return;
            }

            transactionSession.targetVerified = true;
            transactionSession.targetDevice = deviceId;

            transactionSession.state =
                TRANSACTION_PROCESSING;

            Serial.println();
            Serial.println("RECEIVER VERIFIED");
            Serial.println("PROCESSING TRANSACTION");

            sendTransactionState(
                "transaction_processing"
            );

            bool success = executeTransaction();

            if (success)
            {
                Serial.println("TRANSACTION SUCCESS");

                sendTransactionState(
                    "transaction_success"
                );
            }
            else
            {
                Serial.println("TRANSACTION FAILED");

                sendTransactionState(
                    "transaction_failed"
                );
            }

            break;
        }

        default:
            break;
    }
}