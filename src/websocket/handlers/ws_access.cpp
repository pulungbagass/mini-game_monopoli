#include "ws_access.h"

#include "../../services/ownership_service.h"

#include "../ws_manager.h"

extern AsyncWebSocket ws;

/* ======================================================
   Handle Access Request
====================================================== */

void handleAccess(
    AsyncWebSocketClient *client,
    JsonDocument &doc
)
{
    String role = doc["role"];
    String deviceId = doc["deviceId"];

    bool roleOwned = isRoleOwned(role);

    bool sameOwner = isRoleOwner(
        role,
        deviceId
    );

    bool deviceHasRole = isDeviceRegistered(
        deviceId
    );

    JsonDocument response;

    /* ======================================================
       ACCESS GRANTED
    ====================================================== */

    if (roleOwned && sameOwner)
    {
        response["type"] = "access_granted";
        response["role"] = role;

        Serial.println("ACCESS GRANTED");
    }

    /* ======================================================
       NEED CLAIM
    ====================================================== */

    else if (!roleOwned && !deviceHasRole)
    {
        response["type"] = "need_claim";
        response["role"] = role;

        Serial.println("NEED NFC CLAIM");
    }

    /* ======================================================
       ACCESS DENIED
    ====================================================== */

    else
    {
        response["type"] = "access_denied";
        response["role"] = role;

        Serial.println("ACCESS DENIED");
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