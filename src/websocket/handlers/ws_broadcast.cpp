#include "ws_broadcast.h"

#include "../../data/game_state.h"
#include "../ws_manager.h"

#include <ArduinoJson.h>


extern AsyncWebSocket ws;


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

    Serial.println(
        "GAME STATE BROADCASTED"
    );
}