#pragma once

#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

void handleBuyProperty(
    AsyncWebSocketClient* client,
    JsonDocument& doc);

    void handleSellProperty(
    AsyncWebSocketClient* client,
    JsonDocument& doc
);

void handleMortgageProperty(
    AsyncWebSocketClient* client,
    JsonDocument& doc
);

void handleReleaseMortgage(
    AsyncWebSocketClient* client,
    JsonDocument& doc
);

void handleBuildHouse(
    AsyncWebSocketClient* client,
    JsonDocument& doc
);

void handleSellHouse(
    AsyncWebSocketClient* client,
    JsonDocument& doc
);

void handleBuildHotel(
    AsyncWebSocketClient* client,
    JsonDocument& doc
);

void handleSellHotel(
    AsyncWebSocketClient* client,
    JsonDocument& doc
);