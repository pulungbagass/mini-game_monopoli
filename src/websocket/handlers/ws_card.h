#pragma once

#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

void handleDrawCommunityChest(
    AsyncWebSocketClient *client,
    JsonDocument &doc
);

void handleDrawChance(
    AsyncWebSocketClient *client,
    JsonDocument &doc
);
