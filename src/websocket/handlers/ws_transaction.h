#ifndef WS_TRANSACTION_H
#define WS_TRANSACTION_H

#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

/* ======================================================
   WAIT
====================================================== */

void sendTransactionWaitSource();

void sendTransactionWaitTarget();

/* ======================================================
   RESULT
====================================================== */

void sendTransactionSuccess();

void sendTransactionFailed();

void sendTransactionTimeout();

/* ======================================================
   HANDLER
====================================================== */

void handleTransaction(
    AsyncWebSocketClient *client,
    JsonDocument &doc
);

#endif