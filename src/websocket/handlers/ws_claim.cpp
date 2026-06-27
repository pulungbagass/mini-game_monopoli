#include "ws_claim.h"
#include "../../data/claim_session.h"

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

    Serial.println();
    Serial.println("===== CLAIM REQUEST =====");

    Serial.print("ROLE   : ");
    Serial.println(claimSession.role);

    Serial.print("DEVICE : ");
    Serial.println(claimSession.deviceId);

    Serial.println("STATUS : WAITING NFC TAP");
    Serial.println();
}