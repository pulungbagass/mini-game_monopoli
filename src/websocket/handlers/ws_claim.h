#ifndef WS_CLAIM_H
#define WS_CLAIM_H

#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

extern bool waitingForCard;
extern String pendingRole;
extern String pendingDeviceId;

void handleClaim(
    AsyncWebSocketClient *client,
    JsonDocument &doc
);

#endif