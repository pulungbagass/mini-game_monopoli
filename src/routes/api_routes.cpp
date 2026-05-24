#include "api_routes.h"

#include "../web/web_server.h"
#include "../data/players_data.h"

#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>

extern AsyncWebServer server;


void setupApiRoutes() {

    server.on(
        "/api/players",
        HTTP_GET,

        [](AsyncWebServerRequest *request) {

            JsonDocument doc;

            JsonArray array =
                doc.to<JsonArray>();

            for (int i = 0; i < TOTAL_PLAYERS; i++) {

                JsonObject player =
                    array.add<JsonObject>();

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
            }

            String response;

            serializeJson(
                doc,
                response
            );

            request->send(
                200,
                "application/json",
                response
            );
        }
    );


    server.on(
        "/api/test",
        HTTP_GET,

        [](AsyncWebServerRequest *request) {

            request->send(
                200,
                "application/json",
                "{\"status\":\"ok\"}"
            );
        }
    );

}