#ifndef WS_REGISTER_H
#define WS_REGISTER_H

#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

void handleRegister(
    AsyncWebSocketClient *client,
    JsonDocument &doc
);

#endif