#include "ws_transaction_start.h"

#include "../../data/transaction_session.h"
#include "../../data/session_data.h"
#include "../../services/ownership_service.h"
#include "../../services/transaction_service.h"
#include "../../services/transaction_session_service.h"
#include "../../websocket/handlers/ws_transaction.h"

/* ======================================================
   START TRANSACTION
====================================================== */

void handleTransactionStart(
    AsyncWebSocketClient *client,
    JsonDocument &doc)
{
    /* =========================================
       TRANSACTION BUSY
    ========================================= */

    if (transactionSession.active)
    {
        JsonDocument res;

        res["type"] = "transaction_busy";

        String json;
        serializeJson(res, json);

        client->text(json);
        return;
    }

    /* =========================================
       REQUEST DATA
    ========================================= */

    String targetRole =
        doc["toRole"].as<String>();

    int amount =
        doc["amount"];

    /* =========================================
       VALIDATE TARGET
    ========================================= */

    if (!playerExists(targetRole))
    {
        JsonDocument res;

        res["type"] = "transaction_failed";
        res["reason"] = "target_not_found";

        String json;
        serializeJson(res, json);

        client->text(json);
        return;
    }

    /* =========================================
       GET OWNER
    ========================================= */

    String deviceId =
        getDeviceIdByClientId(client->id());

    String sourceRole =
        getRoleByDevice(deviceId);

    if (sourceRole == "")
    {
        JsonDocument res;

        res["type"] = "transaction_failed";
        res["reason"] = "no_owner";

        String json;
        serializeJson(res, json);

        client->text(json);
        return;
    }

    /* =========================================
       SAME PLAYER
    ========================================= */

    if (sourceRole == targetRole)
    {
        JsonDocument res;

        res["type"] = "transaction_failed";
        res["reason"] = "same_player";

        String json;
        serializeJson(res, json);

        client->text(json);
        return;
    }

    /* =========================================
       INVALID AMOUNT
    ========================================= */

    if (amount <= 0)
    {
        JsonDocument res;

        res["type"] = "transaction_failed";
        res["reason"] = "invalid_amount";

        String json;
        serializeJson(res, json);

        client->text(json);
        return;
    }

    /* =========================================
       CHECK BALANCE
    ========================================= */

    int money =
        getPlayerMoney(sourceRole);

    if (money < amount)
    {
        JsonDocument res;

        res["type"] = "transaction_failed";
        res["reason"] = "insufficient_balance";
        res["balance"] = money;

        String json;
        serializeJson(res, json);

        client->text(json);
        return;
    }

    /* =========================================
       CREATE SESSION
    ========================================= */

    clearTransactionSession();

    transactionSession.active = true;

    transactionSession.type =
        TRANSACTION_TRANSFER;

    transactionSession.state =
        TRANSACTION_WAIT_SENDER;

    transactionSession.sourceRole =
        sourceRole;

    transactionSession.targetRole =
        targetRole;

    transactionSession.amount =
        amount;

    transactionSession.startTime =
        millis();

    transactionSession.sourceVerified =
        false;

    transactionSession.targetVerified =
        false;

    transactionSession.sourceDevice =
        "";

    transactionSession.targetDevice =
        "";

    /* =========================================
       RESPONSE
    ========================================= */

    JsonDocument res;

    res["type"] =
        "transaction_wait_sender";

    String json;
    serializeJson(res, json);

    client->text(json);

    Serial.println();
    Serial.println("========== TRANSACTION ==========");
    Serial.print("DEVICE : ");
    Serial.println(deviceId);
    Serial.print("SOURCE : ");
    Serial.println(sourceRole);
    Serial.print("TARGET : ");
    Serial.println(targetRole);
    Serial.print("AMOUNT : ");
    Serial.println(amount);
    Serial.println("WAITING SENDER NFC");
    Serial.println("=================================");
}