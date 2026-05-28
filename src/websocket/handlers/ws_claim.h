#ifndef WS_CLAIM_H
#define WS_CLAIM_H

#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

void handleClaim(
    AsyncWebSocketClient *client,
    JsonDocument &doc
);

#endif