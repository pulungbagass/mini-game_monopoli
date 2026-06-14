#include "ws_broadcast.h"

#include "../../data/game_state.h"
#include "../../data/session_data.h"

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

    JsonArray players =
        doc["players"]
        .to<JsonArray>();

    for (
        int i = 0;
        i < 7;
        i++
    ) {

        JsonObject player =
            players.add<JsonObject>();

        player["role"] =
            playerStates[i].role;

        player["money"] =
            playerStates[i].money;

        player["property"] =
            playerStates[i].property;
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