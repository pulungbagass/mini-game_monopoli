#include "ws_claim.h"

/* ======================================================
   Claim Session
====================================================== */

bool waitingForCard = false;

String pendingRole = "";

String pendingDeviceId = "";

/* ======================================================
   Handle Claim Request
====================================================== */

void handleClaim(
    AsyncWebSocketClient *client,
    JsonDocument &doc
)
{
    (void)client;

    pendingRole = doc["role"].as<String>();

    pendingDeviceId = doc["deviceId"].as<String>();

    waitingForCard = true;

    Serial.println();
    Serial.println("===== CLAIM REQUEST =====");

    Serial.print("ROLE   : ");
    Serial.println(pendingRole);

    Serial.print("DEVICE : ");
    Serial.println(pendingDeviceId);

    Serial.println("STATUS : WAITING NFC TAP");
    Serial.println();
}