#include "transaction_session_service.h"
#include "../data/transaction_session.h"

/* ======================================================
   Start Transaction
====================================================== */

bool startTransaction(
    const String& sourceRole,
    const String& targetRole,
    int amount
)
{
    if (transactionSession.active)
        return false;

    clearTransactionSession();

    transactionSession.active = true;

    transactionSession.state =
        TRANSACTION_WAIT_SENDER;

    transactionSession.sourceRole =
        sourceRole;

    transactionSession.targetRole =
        targetRole;

    transactionSession.amount =
        amount;

    return true;
}

/* ======================================================
   Cancel
====================================================== */

void cancelTransaction()
{
    Serial.println();
    Serial.println("TRANSACTION CANCELLED");

    finishTransaction();
}

/* ======================================================
   Finish
====================================================== */

/* ======================================================
   Finish
====================================================== */

void finishTransaction()
{
    Serial.println();
    Serial.println("========== TRANSACTION END ==========");

    clearTransactionSession();

    Serial.println("SESSION CLEARED");
    Serial.println("=====================================");
}

/* ======================================================
   Active
====================================================== */

bool isTransactionActive()
{
    return transactionSession.active;
}