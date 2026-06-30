#include "transaction_session.h"

/* ======================================================
   Global Session
====================================================== */

TransactionSession transactionSession;

/* ======================================================
   Clear Session
====================================================== */

void clearTransactionSession()
{
    transactionSession.active = false;

    transactionSession.type = TRANSACTION_NONE;

    transactionSession.state = TRANSACTION_IDLE;

    transactionSession.sourceRole = "";
    transactionSession.targetRole = "";

    transactionSession.sourceDevice = "";
    transactionSession.targetDevice = "";

    transactionSession.amount = 0;

    transactionSession.startTime = 0;

    transactionSession.sourceVerified = false;
    transactionSession.targetVerified = false;
}