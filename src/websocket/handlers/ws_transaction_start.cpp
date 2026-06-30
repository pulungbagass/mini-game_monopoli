#include "ws_transaction_start.h"

#include "../../services/transaction_session_service.h"
#include "../../data/transaction_session.h"

/* ======================================================
   START TRANSACTION
====================================================== */

void handleTransactionStart(
    AsyncWebSocketClient *client,
    JsonDocument &doc
)
{
    if (transactionSession.active)
    {
        JsonDocument res;

        res["type"] = "transaction_busy";

        String json;
        serializeJson(res, json);

        client->text(json);

        return;
    }

    transactionSession.active = true;

    transactionSession.type =
        TRANSACTION_TRANSFER;

    transactionSession.state =
        TRANSACTION_WAIT_SENDER;

    transactionSession.sourceRole =
        doc["fromRole"].as<String>();

    transactionSession.targetRole =
        doc["toRole"].as<String>();

    transactionSession.amount =
        doc["amount"];

    transactionSession.startTime =
        millis();

    transactionSession.sourceVerified = false;
    transactionSession.targetVerified = false;

    transactionSession.sourceDevice = "";
    transactionSession.targetDevice = "";

    JsonDocument res;

    res["type"] = "transaction_wait_sender";

    String json;
    serializeJson(res, json);

    client->text(json);

    Serial.println();
    Serial.println("========== TRANSACTION ==========");

    Serial.print("SOURCE : ");
    Serial.println(transactionSession.sourceRole);

    Serial.print("TARGET : ");
    Serial.println(transactionSession.targetRole);

    Serial.print("AMOUNT : ");
    Serial.println(transactionSession.amount);

    Serial.println("WAITING SENDER NFC");
    Serial.println("===============================");
}