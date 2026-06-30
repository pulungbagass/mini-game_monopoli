#ifndef WS_TRANSACTION_H
#define WS_TRANSACTION_H

#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

void handleTransaction(
    AsyncWebSocketClient *client,
    JsonDocument &doc
);

#endif