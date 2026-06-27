#pragma once

#include <Arduino.h>

struct TransactionSession
{
    bool active;

    String fromRole;
    String toRole;

    String fromDevice;
    String toDevice;

    int amount;

    bool senderVerified;
    bool receiverVerified;
};

extern TransactionSession transactionSession;

void clearTransactionSession();