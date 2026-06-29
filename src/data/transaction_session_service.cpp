#include "transaction_session_service.h"

#include "../data/transaction_session.h"

/* ======================================================
   Start Transaction
====================================================== */

bool startTransaction(
    const String& fromRole,
    const String& toRole,
    int amount
)
{
    if (transactionSession.active)
        return false;

    transactionSession.active = true;

    transactionSession.type =
        TRANSACTION_TRANSFER;

    transactionSession.state =
        TRANSACTION_WAIT_SENDER;

    transactionSession.startTime =
        millis();

    transactionSession.fromRole =
        fromRole;

    transactionSession.toRole =
        toRole;

    transactionSession.amount =
        amount;

    transactionSession.senderVerified =
        false;

    transactionSession.receiverVerified =
        false;

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