#ifndef WS_TRANSACTION_H
#define WS_TRANSACTION_H

#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

void sendTransactionWaitSource();

void sendTransactionWaitTarget();

void sendTransactionSuccess();

void sendTransactionFailed();

void handleTransaction(
    AsyncWebSocketClient *client,
    JsonDocument &doc
);

#endif