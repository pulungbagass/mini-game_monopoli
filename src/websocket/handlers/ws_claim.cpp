#include "ws_claim.h"
#include "../../data/claim_session.h"

#include <ArduinoJson.h>

extern AsyncWebSocket ws;

/* ======================================================
   Claim Session
====================================================== */

/* ======================================================
   Handle Claim Request
====================================================== */

void handleClaim(
    AsyncWebSocketClient *client,
    JsonDocument &doc
)
{
    (void)client;

    claimSession.role = doc["role"].as<String>();

    claimSession.deviceId = doc["deviceId"].as<String>();

    claimSession.waiting = true;

    claimSession.startTime = millis();

    Serial.println();
    Serial.println("===== CLAIM REQUEST =====");

    Serial.print("ROLE   : ");
    Serial.println(claimSession.role);

    Serial.print("DEVICE : ");
    Serial.println(claimSession.deviceId);

    Serial.println("STATUS : WAITING NFC TAP");
    Serial.println();
}

/* ======================================================
   Claim Timeout
====================================================== */

void sendClaimTimeout()
{
    JsonDocument doc;

    doc["type"] = "claim_timeout";

    doc["role"] = claimSession.role;

    String json;
    serializeJson(doc, json);

    ws.textAll(json);
}