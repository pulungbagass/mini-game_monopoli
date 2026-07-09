#ifndef TRANSACTION_SESSION_SERVICE_H
#define TRANSACTION_SESSION_SERVICE_H

#include <Arduino.h>

/* ======================================================
   Session
====================================================== */

bool startTransaction(
    const String& sourceRole,
    const String& targetRole,
    int amount
);

void cancelTransaction();

void finishTransaction();

bool isTransactionActive();

/* ======================================================
   Verification
====================================================== */

bool verifySender(
    const String& role
);

bool verifyReceiver(
    const String& role
);

/* ======================================================
   Processing
====================================================== */

bool processTransaction();

#endif