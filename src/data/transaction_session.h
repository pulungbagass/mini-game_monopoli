#ifndef TRANSACTION_SESSION_H
#define TRANSACTION_SESSION_H

#include <Arduino.h>

/* ======================================================
   Transaction Session
====================================================== */

struct TransactionSession
{
    bool active;

    TransactionState state;

    String fromRole;
    String toRole;

    String fromDevice;
    String toDevice;

    int amount;

    bool senderVerified;
    bool receiverVerified;
};

/* ======================================================
   Transaction State
====================================================== */

enum TransactionState
{
    TRANSACTION_IDLE,

    TRANSACTION_WAIT_SENDER,

    TRANSACTION_WAIT_RECEIVER,

    TRANSACTION_PROCESSING,

    TRANSACTION_SUCCESS,

    TRANSACTION_FAILED
};


extern TransactionSession transactionSession;

/* ======================================================
   Session Helper
====================================================== */

void clearTransactionSession();

#endif