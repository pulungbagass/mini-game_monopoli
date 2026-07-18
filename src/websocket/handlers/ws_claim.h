#ifndef WS_CLAIM_H
#define WS_CLAIM_H

#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>


void handleClaim(
    AsyncWebSocketClient *client,
    JsonDocument &doc
);

void sendClaimTimeout();

void sendClaimWrongCard(const String& deviceId);

void sendClaimAlreadyOwned(const String& deviceId, const String& role);

#endif