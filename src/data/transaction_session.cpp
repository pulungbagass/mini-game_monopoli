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

   transactionSession.type =
      TRANSACTION_NONE;

   transactionSession.propertyAction =
      PROPERTY_NONE;

   transactionSession.state =
      TRANSACTION_IDLE;

   transactionSession.assetId = "";

   transactionSession.sourceRole = "";
   transactionSession.targetRole = "";

   transactionSession.sourceDevice = "";
   transactionSession.targetDevice = "";

   transactionSession.amount = 0;

   transactionSession.startTime = 0;

   transactionSession.sourceVerified = false;
   transactionSession.targetVerified = false;
}

/* ======================================================
   Set Transaction State
====================================================== */

void setTransactionState(
    TransactionState state)
{
    transactionSession.state = state;
}

/* ======================================================
   Next Transaction State
====================================================== */

bool nextTransactionState()
{
   switch (transactionSession.state)
   {
      case TRANSACTION_WAIT_SENDER:
         transactionSession.state =
               TRANSACTION_WAIT_RECEIVER;
         return true;

      case TRANSACTION_WAIT_RECEIVER:
         transactionSession.state =
               TRANSACTION_PROCESSING;
         return true;
      case TRANSACTION_PROCESSING:
         transactionSession.state =
               TRANSACTION_SUCCESS;
         return true;

      case TRANSACTION_SUCCESS:
         transactionSession.state =
               TRANSACTION_IDLE;
         return true;

      case TRANSACTION_FAILED:
         transactionSession.state =
               TRANSACTION_IDLE;
         return true;

      default:
         return false;
   }
}

/* ======================================================
   Reset Verification
====================================================== */

void resetTransactionVerification()
{
   transactionSession.sourceVerified = false;
   transactionSession.targetVerified = false;
}

/* ======================================================
   Verify Sender
====================================================== */

void verifyTransactionSender()
{
   transactionSession.sourceVerified = true;
}

/* ======================================================
   Verify Receiver
====================================================== */

void verifyTransactionReceiver()
{
   transactionSession.targetVerified = true;
}

/* ======================================================
   State Helper
====================================================== */

bool isWaitingSender()
{
   return transactionSession.state ==
      TRANSACTION_WAIT_SENDER;
}

bool isWaitingReceiver()
{
   return transactionSession.state ==
      TRANSACTION_WAIT_RECEIVER;
}

bool isTransactionProcessing()
{
   return transactionSession.state ==
      TRANSACTION_PROCESSING;
}

bool isTransactionSuccess()
{
   return transactionSession.state ==
      TRANSACTION_SUCCESS;
}

bool isTransactionFailed()
{
   return transactionSession.state == 
      TRANSACTION_FAILED;
}