#ifndef TRANSACTION_SESSION_SERVICE_H
#define TRANSACTION_SESSION_SERVICE_H

#include <Arduino.h>
#include "../data/transaction_session.h"

/* ======================================================
   Session
====================================================== */

bool startTransaction(
    TransactionType type,
    PropertyAction propertyAction,
    const String& sourceRole,
    const String& targetRole,
    const String& assetId,
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

// ==========================================================
// Property Transaction
// ==========================================================

bool startBuyPropertyTransaction(
    const String& buyerRole,
    const String& assetId
);

bool startSellPropertyTransaction(
    const String& sellerRole,
    const String& assetId
);

bool startRentTransaction(
    const String& payerRole,
    const String& assetId,
    int diceValue
);

#endif