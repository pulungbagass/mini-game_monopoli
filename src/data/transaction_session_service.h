#ifndef TRANSACTION_SESSION_SERVICE_H
#define TRANSACTION_SESSION_SERVICE_H

#include <Arduino.h>

/* ======================================================
   Session
====================================================== */

bool startTransaction(
    const String& fromRole,
    const String& toRole,
    int amount
);

void cancelTransaction();

void finishTransaction();

bool isTransactionActive();

#endif