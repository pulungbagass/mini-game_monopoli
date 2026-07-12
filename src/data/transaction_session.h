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

// ====================================================
// Property Action
// ====================================================

enum PropertyAction
{
   PROPERTY_NONE,

   PROPERTY_BUY,
   PROPERTY_SELL,

   PROPERTY_PAY_RENT,

   PROPERTY_MORTGAGE,
   PROPERTY_RELEASE,

   PROPERTY_BUILD_HOUSE,
   PROPERTY_SELL_HOUSE,

   PROPERTY_BUILD_HOTEL,
   PROPERTY_SELL_HOTEL,

   PROPERTY_TRANSFER
};

/* ======================================================
   Transaction Session
====================================================== */

struct TransactionSession
{
   bool active;

   TransactionType type;
   PropertyAction propertyAction;
   TransactionState state;

   /* =========================
      Transaction Info
   ========================= */

   String assetId;

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

void setTransactionState(
    TransactionState state
);

bool nextTransactionState();

void resetTransactionVerification();

void verifyTransactionSender();

void verifyTransactionReceiver();

bool isWaitingSender();

bool isWaitingReceiver();

bool isTransactionProcessing();

bool isTransactionSuccess();

bool isTransactionFailed();

#endif