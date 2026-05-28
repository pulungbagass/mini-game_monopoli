#include "ws_register.h"

#include "../../data/session_data.h"


void handleRegister(
    AsyncWebSocketClient *client,
    JsonDocument &doc
) {

    String deviceId =
        doc["deviceId"];

    bool found = false;

    /* =========================
       RECONNECT
    ========================= */

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

    /* =========================
       NEW DEVICE
    ========================= */

    if (!found) {

        for (
            int i = 0;
            i < MAX_CLIENTS;
            i++
        ) {

            if (
                clients[i].deviceId == ""
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

    /* =========================
       DEBUG
    ========================= */

    Serial.println(
        "===== CLIENT LIST ====="
    );

    for (
        int i = 0;
        i < MAX_CLIENTS;
        i++
    ) {

        if (
            clients[i].deviceId != ""
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