#include "ws_broadcast.h"

#include "../../data/game_state.h"
#include "../../data/session_data.h"
#include "../../data/players_data.h"

#include "../ws_manager.h"

#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>


extern AsyncWebSocket ws;


/* =========================
   GAME STATE
========================= */

void broadcastGameState() {

    JsonDocument doc;

    doc["type"] =
        "game_state";

    JsonArray jsonPlayers =
    doc["players"].to<JsonArray>();

/* =========================
BANK
========================= */

{
    JsonObject bank = jsonPlayers.add<JsonObject>();

    bank["role"] = "BANK";
    bank["name"] = "BANK";
    bank["uid"] = "BANK";

    bank["money"] =
    bankState.money;

    bank["house"] = 0;
    bank["hotel"] = 0;
    bank["property"] = 0;
}

/* =========================
PLAYERS
========================= */

for (int i = 0; i < TOTAL_PLAYERS; i++)
{
    JsonObject player =
        jsonPlayers.add<JsonObject>();

    player["role"] =
        players[i].role;

    player["uid"] =
        players[i].uid;

    player["name"] =
        players[i].name;

    player["money"] =
        players[i].money;

    player["house"] =
        players[i].house;

    player["hotel"] =
        players[i].hotel;

    player["property"] =
        players[i].house +
        players[i].hotel;
}

    String response;

    serializeJson(
        doc,
        response
    );

    ws.textAll(
        response
    );
}


/* =========================
   ACCESS GRANTED
========================= */

void sendAccessGranted(
    String role,
    String deviceId
) {

    JsonDocument doc;

    doc["type"] =
        "access_granted";

    doc["role"] =
        role;

    String response;

    serializeJson(
        doc,
        response
    );

    for (
        int i = 0;
        i < MAX_CLIENTS;
        i++
    ) {

        if (
            clients[i].deviceId ==
            deviceId
        ) {

            ws.text(
                clients[i].clientId,
                response
            );

            Serial.println(
                "ACCESS RESPONSE SENT"
            );

            break;
        }
    }
}