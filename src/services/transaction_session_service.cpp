#include "transaction_session_service.h"
#include "../data/transaction_session.h"

/* ======================================================
   Start Transaction
====================================================== */

bool startTransaction(
    const String& sourceRole,
    const String& targetRole,
    int amount)
{
    if (transactionSession.active)
        return false;

    clearTransactionSession();

    transactionSession.active = true;

    transactionSession.sourceRole = sourceRole;
    transactionSession.targetRole = targetRole;

    transactionSession.amount = amount;
    transactionSession.startTime = millis();

    resetTransactionVerification();

    setTransactionState(
        TRANSACTION_WAIT_SENDER);

    return true;
}

/* ======================================================
   Cancel
====================================================== */
void cancelTransaction()
{
    if (!transactionSession.active)
        return;

    setTransactionState(TRANSACTION_FAILED);

    clearTransactionSession();
}
/* ======================================================
   Finish
====================================================== */

void finishTransaction()
{
    if (!transactionSession.active)
        return;

    setTransactionState(
        TRANSACTION_SUCCESS);

    clearTransactionSession();
}

/* ======================================================
   Active
====================================================== */

bool isTransactionActive()
{
    return transactionSession.active;
}


/* ======================================================
   Verify Sender
====================================================== */

bool verifySender(
    const String& role)
{
    if (!transactionSession.active)
        return false;

    if (!isWaitingSender())
        return false;

    if (transactionSession.sourceRole != role)
        return false;

    verifyTransactionSender();

    nextTransactionState();

    return true;
}

/* ======================================================
   Verify Receiver
====================================================== */

bool verifyReceiver(
    const String& role)
{
    if (!transactionSession.active)
        return false;

    if (!isWaitingReceiver())
        return false;

    if (transactionSession.targetRole != role)
        return false;

    verifyTransactionReceiver();

    nextTransactionState();

    return true;
}

/* ======================================================
   Process Transaction
====================================================== */

bool processTransaction()
{
    if (!transactionSession.active)
        return false;

    if (!isTransactionProcessing())
        return false;

    return true;
}