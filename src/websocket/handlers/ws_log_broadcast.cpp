#include "ws_log_broadcast.h"

#include "../../data/game_log.h"
#include "../ws_manager.h"

#include <ArduinoJson.h>

extern AsyncWebSocket ws;

/* ======================================================
   BROADCAST SINGLE ENTRY (real-time)
====================================================== */

void broadcastGameLogEntry(
    const GameLogEntry& entry
)
{
    JsonDocument doc;

    doc["type"] = "game_log_entry";

    doc["timestamp"] = entry.timestamp;
    doc["category"] = logCategoryToString(entry.category);
    doc["message"] = entry.message;
    doc["roleA"] = entry.roleA;
    doc["roleB"] = entry.roleB;

    String response;
    serializeJson(doc, response);

    ws.textAll(response);
}

/* ======================================================
   SNAPSHOT (saat client baru connect)
====================================================== */

void sendGameLogSnapshot(
    AsyncWebSocketClient* client
)
{
    JsonDocument doc;

    doc["type"] = "game_log_state";

    JsonArray entries =
        doc["entries"].to<JsonArray>();

    int total = getGameLogCount();

    for (int i = 0; i < total; i++)
    {
        const GameLogEntry& entry =
            getGameLogAt(i);

        JsonObject item = entries.add<JsonObject>();

        item["timestamp"] = entry.timestamp;
        item["category"] = logCategoryToString(entry.category);
        item["message"] = entry.message;
        item["roleA"] = entry.roleA;
        item["roleB"] = entry.roleB;
    }

    String response;
    serializeJson(doc, response);

    client->text(response);
}
