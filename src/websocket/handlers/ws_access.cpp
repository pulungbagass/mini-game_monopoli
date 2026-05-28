#include "ws_access.h"

#include "../../data/ownership_data.h"
#include "../ws_manager.h"


extern AsyncWebSocket ws;


void handleAccess(
    AsyncWebSocketClient *client,
    JsonDocument &doc
) {

    String role =
        doc["role"];

    String deviceId =
        doc["deviceId"];

    bool roleOwned =
        false;

    bool sameOwner =
        false;

    bool deviceHasRole =
        false;

    for (
        int i = 0;
        i < 7;
        i++
    ) {

        if (
            ownerships[i].role ==
            role
        ) {

            roleOwned = true;

            if (
                ownerships[i].deviceId ==
                deviceId
            ) {

                sameOwner = true;
            }
        }

        if (
            ownerships[i].deviceId ==
            deviceId
        ) {

            deviceHasRole = true;
        }
    }

    JsonDocument response;

    /* =========================
       ACCESS GRANTED
    ========================= */

    if (
        roleOwned &&
        sameOwner
    ) {

        response["type"] =
            "access_granted";

        response["role"] =
            role;

        Serial.println(
            "ACCESS GRANTED"
        );
    }

    /* =========================
       NEED CLAIM
    ========================= */

    else if (
        !roleOwned &&
        !deviceHasRole
    ) {

        response["type"] =
            "need_claim";

        response["role"] =
            role;

        Serial.println(
            "NEED NFC CLAIM"
        );
    }

    /* =========================
       DENIED
    ========================= */

    else {

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