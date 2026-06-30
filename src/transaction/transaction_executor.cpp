#include "transaction_executor.h"

#include "../data/transaction_session.h"
#include "../services/transaction_service.h"
#include "../services/transaction_session_service.h"

/* ======================================================
   Execute Transaction
====================================================== */

bool executeTransaction()
{
    if (!transactionSession.active)
        return false;

    if (!transactionSession.sourceVerified)
        return false;

    if (!transactionSession.targetVerified)
        return false;

    bool success = transferMoney(
        transactionSession.sourceRole,
        transactionSession.targetRole,
        transactionSession.amount
    );

    if (!success)
    {
        transactionSession.state = TRANSACTION_FAILED;
        return false;
    }

    transactionSession.state = TRANSACTION_SUCCESS;

    finishTransaction();

    return true;
}