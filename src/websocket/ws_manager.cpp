#include "ws_manager.h"

#include "../web/web_server.h"
#include "../data/session_data.h"
#include "../data/ownership_data.h"

#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>


/* =========================
   WEBSOCKET INSTANCE
========================= */

AsyncWebSocket ws("/ws");


/* =========================
   HANDLE EVENT
========================= */

void onWebSocketEvent(
    AsyncWebSocket *server,
    AsyncWebSocketClient *client,
    AwsEventType type,
    void *arg,
    uint8_t *data,
    size_t len
) {

    switch (type) {

        /* =========================
           CONNECT
        ========================= */

        case WS_EVT_CONNECT:
            Serial.println(
                "CLIENT CONNECTED"
            );
            Serial.print(
                "CLIENT ID : "
            );
            Serial.println(
                client->id()
            );
            client->text(
                "CONNECTED TO ESP32"
            );
            break;

        /* =========================
           DISCONNECT
        ========================= */

        case WS_EVT_DISCONNECT:
            Serial.println(
                "CLIENT DISCONNECTED"
            );
            Serial.print(
                "CLIENT ID : "
            );
            Serial.println(
                client->id()
            );
            break;

        /* =========================
           DATA
        ========================= */

        case WS_EVT_DATA: {
            AwsFrameInfo *info =
                (AwsFrameInfo*)arg;
            if (
                info->opcode != WS_TEXT
            ) {
                return;
            }

            String message = "";

            for (
                size_t i = 0;
                i < len;
                i++
            ) {
                message +=
                    (char)data[i];
            }

            Serial.println(
                "MESSAGE RECEIVED:"
            );

            Serial.println(
                message
            );

            JsonDocument doc;

            deserializeJson(
                doc,
                message
            );

            String msgType =
                doc["type"];


            /* =========================
               REGISTER DEVICE
            ========================= */

            if (
                msgType == "register"
            ) {
                String deviceId =
                    doc["deviceId"];

                bool found = false;

                for (
                    int i = 0;
                    i < MAX_CLIENTS;
                    i++
                ) {

                    if (
                        clients[i].deviceId ==
                        deviceId
                    ) {
                        clients[i].clientId =
                            client->id();
                        clients[i].connected =
                            true;
                        found = true;
                        Serial.println(
                            "DEVICE RECONNECTED"
                        );
                        break;
                    }
                }

                if (!found) {

                    for (
                        int i = 0;
                        i < MAX_CLIENTS;
                        i++
                    ) {

                        if (
                            clients[i].deviceId ==
                            ""
                        ) {
                            clients[i].deviceId =
                                deviceId;
                            clients[i].clientId =
                                client->id();
                            clients[i].connected =
                                true;
                            Serial.println(
                                "NEW DEVICE REGISTERED"
                            );
                            break;
                        }
                    }
                }

                Serial.println(
                    "===== CLIENT LIST ====="
                );

                for (
                    int i = 0;
                    i < MAX_CLIENTS;
                    i++
                ) {

                    if (
                        clients[i].deviceId !=
                        ""
                    ) {
                        Serial.print(
                            "DEVICE : "
                        );
                        Serial.println(
                            clients[i].deviceId
                        );
                        Serial.print(
                            "CLIENT : "
                        );
                        Serial.println(
                            clients[i].clientId
                        );
                        Serial.print(
                            "CONNECTED : "
                        );
                        Serial.println(
                            clients[i].connected
                        );
                        Serial.println();
                    }
                }
            }


            /* =========================
               CLAIM ROLE
            ========================= */
            if (
                msgType == "claim_role"
            ) {
                String role =
                    doc["role"];
                String deviceId =
                    doc["deviceId"];

                pendingRole =
                    role;
                pendingDeviceId =
                    deviceId;
                waitingForCard =
                    true;

                Serial.println(
                    "===== CLAIM REQUEST ====="
                );
                Serial.print(
                    "ROLE : "
                );
                Serial.println(
                    role
                );
                Serial.print(
                    "DEVICE : "
                );
                Serial.println(
                    deviceId
                );
                Serial.println(
                    "WAITING NFC TAP..."
                );
            }


            /* =========================
               ACCESS REQUEST
            ========================= */

            if (
                msgType ==
                "request_access"
            ) {
                String role =
                    doc["role"];
                String deviceId =
                    doc["deviceId"];

                bool accessGranted =
                    false;

                for (
                    int i = 0;
                    i < 7;
                    i++
                ) {

                    if (
                        ownerships[i].role ==
                        role
                        &&
                        ownerships[i].deviceId ==
                        deviceId
                    ) {
                        accessGranted =
                            true;
                        break;
                    }
                }

                JsonDocument response;

                if (accessGranted) {
                    response["type"] =
                        "access_granted";
                    response["role"] =
                        role;
                    Serial.println(
                        "ACCESS GRANTED"
                    );

                } else {
                    response["type"] =
                        "access_denied";
                    response["role"] =
                        role;
                    Serial.println(
                        "ACCESS DENIED"
                    );
                }

                String jsonResponse;

                serializeJson(
                    response,
                    jsonResponse
                );

                ws.text(
                    client->id(),
                    jsonResponse
                );
            }
            break;
        }


        /* =========================
           OTHER
        ========================= */

        case WS_EVT_PONG:
        case WS_EVT_ERROR:

            break;
    }
}


/* =========================
   INIT WEBSOCKET
========================= */

void initWebSocket() {

    ws.onEvent(
        onWebSocketEvent
    );

    server.addHandler(&ws);

    Serial.println(
        "WEBSOCKET READY"
    );
}