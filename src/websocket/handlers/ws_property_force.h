#pragma once

#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

/* ======================================================
   BANK EMERGENCY ACTIONS

   Beda dengan mortgage/sell biasa (yang wajib tap kartu
   NFC owner untuk konfirmasi), force_mortgage & force_sell
   dieksekusi LANGSUNG oleh Bank tanpa perlu tap kartu
   fisik player -- dipakai kalau player membandel / tidak
   bisa/mau tap kartu (classic Monopoly "emergency" rule).

   HANYA role == "BANK" yang boleh memanggil ini.
====================================================== */

void handleForceMortgage(
    AsyncWebSocketClient *client,
    JsonDocument &doc
);

void handleForceSell(
    AsyncWebSocketClient *client,
    JsonDocument &doc
);
