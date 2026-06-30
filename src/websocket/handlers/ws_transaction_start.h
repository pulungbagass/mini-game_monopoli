#pragma once

#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

void handleTransactionStart(
    AsyncWebSocketClient *client,
    JsonDocument &doc
);