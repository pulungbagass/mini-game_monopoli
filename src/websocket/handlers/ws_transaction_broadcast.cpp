#include "ws_transaction_broadcast.h"

#include "../ws_manager.h"

#include <ArduinoJson.h>

extern AsyncWebSocket ws;

/* ======================================================
   TRANSACTION STATE
====================================================== */

void sendTransactionState(
    const String& type
)
{
    JsonDocument doc;

    doc["type"] = type;

    String json;

    serializeJson(doc, json);

    ws.textAll(json);
}