#ifndef WS_TRANSACTION_CANCEL_H
#define WS_TRANSACTION_CANCEL_H

#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

void handleTransactionCancel(
    AsyncWebSocketClient *client,
    JsonDocument &doc
);

#endif