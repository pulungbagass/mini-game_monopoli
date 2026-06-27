#include "transaction_session.h"

TransactionSession transactionSession;

void clearTransactionSession()
{
    transactionSession.active = false;

    transactionSession.fromRole = "";
    transactionSession.toRole = "";

    transactionSession.fromDevice = "";
    transactionSession.toDevice = "";

    transactionSession.amount = 0;

    transactionSession.senderVerified = false;
    transactionSession.receiverVerified = false;
}