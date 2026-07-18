#include "ws_claim.h"
#include "../../data/claim_session.h"
#include "../../data/session_data.h"

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

/* ======================================================
   Claim Wrong Card
   (kartu yang di-tap tidak sesuai role yang diklaim,
   sesi TETAP terbuka - user boleh tap ulang)
====================================================== */

void sendClaimWrongCard(const String& deviceId)
{
    JsonDocument doc;

    doc["type"] = "claim_wrong_card";

    doc["role"] = claimSession.role;

    String json;
    serializeJson(doc, json);

    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        if (clients[i].deviceId == deviceId)
        {
            ws.text(clients[i].clientId, json);
            break;
        }
    }
}

/* ======================================================
   Claim Already Owned
   (role yang mau diklaim ternyata sudah dimiliki
   device lain, sesi ditutup - user harus pilih role lain)
====================================================== */

void sendClaimAlreadyOwned(const String& deviceId, const String& role)
{
    JsonDocument doc;

    doc["type"] = "claim_already_owned";

    doc["role"] = role;

    String json;
    serializeJson(doc, json);

    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        if (clients[i].deviceId == deviceId)
        {
            ws.text(clients[i].clientId, json);
            break;
        }
    }
}