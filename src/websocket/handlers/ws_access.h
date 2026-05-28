#ifndef WS_ACCESS_H
#define WS_ACCESS_H

#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

void handleAccess(
    AsyncWebSocketClient *client,
    JsonDocument &doc
);

#endif