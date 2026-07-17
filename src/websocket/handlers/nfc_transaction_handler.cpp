#include "nfc_transaction_handler.h"

#include "../../data/transaction_session.h"

#include "../../services/transaction_session_service.h"

#include "../../transaction/transaction_executor.h"

#include "ws_transaction_broadcast.h"

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
            /* Shortcut: target BANK / property (tidak perlu
               tap kedua) -> langsung proses. */

            nextTransactionState();
            executeTransaction();
        }
        else if (isWaitingReceiver())
        {
            /* Kasus normal player -> player: sender sudah
               tap, sekarang giliran receiver tap.
               Frontend perlu diberi tahu supaya banner
               ganti dari "Tap Sender" ke "Tap Receiver". */

            sendTransactionState("transaction_wait_receiver");
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