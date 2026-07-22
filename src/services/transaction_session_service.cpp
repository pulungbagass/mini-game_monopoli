#include "transaction_session_service.h"
#include "../data/transaction_session.h"

#include "../transaction/transaction_executor.h"
#include "../transaction/property_transaction_executor.h"
#include "../transaction/bank_transaction_executor.h"
#include "../transaction/auction_transaction_executor.h"

#include "../transaction/transaction_handler.h"
#include "transaction_service.h"

/* ======================================================
   Start Transaction
====================================================== */

bool startTransaction(
    TransactionType type,
    PropertyAction propertyAction,
    const String& sourceRole,
    const String& targetRole,
    const String& assetId,
    int amount
)
{
    if (transactionSession.active)
        return false;

    clearTransactionSession();

    transactionSession.active = true;

    transactionSession.type =
        type;

    transactionSession.propertyAction =
        propertyAction;

    transactionSession.sourceRole =
        sourceRole;

    transactionSession.targetRole =
        targetRole;

    transactionSession.assetId =
        assetId;

    transactionSession.amount =
        amount;

    transactionSession.startTime =
        millis();

    resetTransactionVerification();

    /* =========================================
       TARGET KOSONG -> TIDAK ADA PENERIMA
       (kasus PROPERTY: cuma owner/buyer yang
       perlu tap, tidak ada pihak kedua)
    ========================================= */

    if (targetRole == "")
    {
        transactionSession.targetVerified = true;
    }

    setTransactionState(
        TRANSACTION_WAIT_SENDER
    );

    return true;
}

/* ======================================================
   Cancel
====================================================== */
void cancelTransaction()
{
    if (!transactionSession.active)
        return;

    setTransactionState(TRANSACTION_FAILED);

    clearTransactionSession();
}
/* ======================================================
   Finish
====================================================== */

void finishTransaction(bool success)
{
    if (!transactionSession.active)
        return;

    // BUG FIX: sebelumnya selalu di-set TRANSACTION_SUCCESS
    // walau transaksinya sebenarnya gagal. Session langsung
    // di-clear sesudah ini jadi dampaknya kecil, tapi state
    // akhir yang dicatat harus mencerminkan hasil asli.
    setTransactionState(
        success ? TRANSACTION_SUCCESS : TRANSACTION_FAILED);

    clearTransactionSession();
}

/* ======================================================
   Active
====================================================== */

bool isTransactionActive()
{
    return transactionSession.active;
}


/* ======================================================
   Verify Sender
====================================================== */

bool verifySender(
    const String& role)
{
    if (!transactionSession.active)
        return false;

    if (!isWaitingSender())
        return false;

    if (transactionSession.sourceRole != role)
        return false;

    verifyTransactionSender();

    nextTransactionState();

    return true;
}

/* ======================================================
   Verify Receiver
====================================================== */

bool verifyReceiver(
    const String& role)
{
    if (!transactionSession.active)
        return false;

    if (!isWaitingReceiver())
        return false;

    if (transactionSession.targetRole != role)
        return false;

    verifyTransactionReceiver();

    nextTransactionState();

    return true;
}

/* ======================================================
   Process Transaction
====================================================== */

bool processTransaction()
{
    if (!transactionSession.active)
        return false;

    if (!isTransactionProcessing())
        return false;

    bool success = false;

    switch (transactionSession.type)
    {
        case TRANSACTION_TRANSFER:
        {
            success = transferMoney(
                transactionSession.sourceRole,
                transactionSession.targetRole,
                transactionSession.amount
            );
            break;
        }

        case TRANSACTION_BANK:
        {
            success = transferMoney(
                transactionSession.sourceRole,
                transactionSession.targetRole,
                transactionSession.amount
            );
            break;
        }

        case TRANSACTION_PROPERTY:
        {
            success = executePropertyTransaction();
            break;
        }

        case TRANSACTION_AUCTION:
        {
            success = false;
            break;
        }

        default:
        {
            success = false;
            break;
        }
    }

    if (success)
    {
        setTransactionState(
            TRANSACTION_SUCCESS
        );
    }
    else
    {
        setTransactionState(
            TRANSACTION_FAILED
        );
    }

    return success;
}