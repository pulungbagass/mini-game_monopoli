#include "nfc_transaction_handler.h"

#include "../../data/transaction_session.h"

#include "../../services/transaction_session_service.h"

#include "../../transaction/transaction_executor.h"

bool handleTransactionCard(
    const String& role)
{
    if (!transactionSession.active)
        return false;

    if (isWaitingSender())
    {
        if (!verifySender(role))
            return false;

        if (transactionSession.targetVerified &&
            isWaitingReceiver())
        {
            nextTransactionState();
            executeTransaction();
        }

        return true;
    }

    if (isWaitingReceiver())
    {
        if (!verifyReceiver(role))
            return false;
        executeTransaction();
        return true;
    }

    return false;
}