#pragma once

#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

/* ======================================================
   AUCTION MESSAGE HANDLERS

   Mengikuti konvensi handler lain di project ini (mis.
   ws_property.cpp / ws_card.cpp): role dipercaya dari
   payload karena halaman private cuma bisa diakses
   setelah NFC access-granted di frontend.
====================================================== */

void handleStartAuction(
    AsyncWebSocketClient *client,
    JsonDocument &doc
);

void handlePlaceBid(
    AsyncWebSocketClient *client,
    JsonDocument &doc
);

void handleEndAuction(
    AsyncWebSocketClient *client,
    JsonDocument &doc
);
