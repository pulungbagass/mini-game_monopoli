#ifndef TRANSACTION_SESSION_H
#define TRANSACTION_SESSION_H

#include <Arduino.h>

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

/* ======================================================
   Transaction Type
====================================================== */

enum TransactionType
{
    TRANSACTION_NONE,
    TRANSACTION_TRANSFER,
    TRANSACTION_BANK,
    TRANSACTION_AUCTION,
    TRANSACTION_PROPERTY
};

/* ======================================================
   Transaction Session
====================================================== */

struct TransactionSession
{
    bool active;

    TransactionType type;
    TransactionState state;

    /* =========================
       Transaction Info
    ========================= */

    String sourceRole;
    String targetRole;

    String sourceDevice;
    String targetDevice;

    int amount;

    unsigned long startTime;

    /* =========================
       Verification
    ========================= */

    bool sourceVerified;
    bool targetVerified;
};

extern TransactionSession transactionSession;

/* ======================================================
   Session Helper
====================================================== */

void clearTransactionSession();

#endif