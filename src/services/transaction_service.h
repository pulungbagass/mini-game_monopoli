#ifndef TRANSACTION_SERVICE_H
#define TRANSACTION_SERVICE_H

#include <Arduino.h>


/* ======================================================
   Transaction Service
====================================================== */

bool addMoney(
    const String& role,
    int amount
);

bool deductMoney(
    const String& role,
    int amount
);

bool transferMoney(
    const String& fromRole,
    const String& toRole,
    int amount
);

#endif