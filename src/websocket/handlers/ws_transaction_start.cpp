#include "ws_transaction_start.h"

#include "../../data/session_data.h"
#include "../../data/transaction_session.h"

#include "../../services/ownership_service.h"
#include "../../services/transaction_service.h"
#include "../../services/transaction_session_service.h"

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
       REQUEST
    ========================================= */

    String targetRole =
        doc["toRole"].as<String>();

    int amount =
        doc["amount"].as<int>();

    /* =========================================
       GET OWNER
    ========================================= */

    String deviceId =
        getDeviceIdByClientId(client->id());

    String sourceRole;

    if (deviceId != "")
    {
        sourceRole =
            getRoleByDevice(deviceId);
    }

    /* =========================================
       BANK HAS NO DEVICE
    ========================================= */

    if (sourceRole == "")
    {
        sourceRole = "BANK";
    }

    /* =========================================
       VALIDATE TARGET
    ========================================= */

    if (
        targetRole != "BANK" &&
        !playerExists(targetRole)
    )
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
       SAME ROLE
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

    if (
        sourceRole != "BANK" &&
        getPlayerMoney(sourceRole) < amount
    )
    {
        JsonDocument res;

        res["type"] = "transaction_failed";
        res["reason"] = "insufficient_balance";

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
       BANK DOESN'T NEED NFC (AS SOURCE)
    ========================================= */

    if (sourceRole == "BANK")
    {
        transactionSession.sourceVerified = true;

        transactionSession.state =
            TRANSACTION_WAIT_RECEIVER;
    }

    /* =========================================
       BANK DOESN'T NEED NFC (AS TARGET)
    ========================================= */

    if (targetRole == "BANK")
    {
        transactionSession.targetVerified = true;
    }

    /* =========================================
       RESPONSE
    ========================================= */

    JsonDocument res;

    if (sourceRole == "BANK")
    {
        res["type"] = "transaction_wait_receiver";
    }
    else
    {
        res["type"] = "transaction_wait_sender";
    }

    res["fromRole"] =
        sourceRole;

    res["toRole"] =
        targetRole;

    res["amount"] =
        amount;

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

    if (sourceRole == "BANK")
    {
        Serial.println("BANK AUTO VERIFIED");
        Serial.println("WAITING RECEIVER NFC");
    }
    else
    {
        Serial.println("WAITING SENDER NFC");
    }

    Serial.println("=================================");
}