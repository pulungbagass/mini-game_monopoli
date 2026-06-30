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
    clearTransactionSession();
}

/* ======================================================
   Finish
====================================================== */

void finishTransaction()
{
    clearTransactionSession();
}

/* ======================================================
   Active
====================================================== */

bool isTransactionActive()
{
    return transactionSession.active;
}