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

    transactionSession.state = TRANSACTION_IDLE;

    transactionSession.fromRole = "";
    transactionSession.toRole = "";

    transactionSession.fromDevice = "";
    transactionSession.toDevice = "";

    transactionSession.amount = 0;

    transactionSession.senderVerified = false;
    transactionSession.receiverVerified = false;
}