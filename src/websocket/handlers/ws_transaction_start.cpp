#include "ws_transaction_start.h"

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

    transactionSession.state =
        TRANSACTION_WAIT_SENDER;

    transactionSession.fromRole =
        doc["fromRole"].as<String>();

    transactionSession.toRole =
        doc["toRole"].as<String>();

    transactionSession.amount =
        doc["amount"];

    transactionSession.senderVerified = false;
    transactionSession.receiverVerified = false;

    transactionSession.fromDevice = "";
    transactionSession.toDevice = "";

    JsonDocument res;

    res["type"] = "transaction_wait_sender";

    String json;

    serializeJson(res, json);

    client->text(json);

    Serial.println();
    Serial.println("========== TRANSACTION ==========");

    Serial.print("FROM : ");
    Serial.println(transactionSession.fromRole);

    Serial.print("TO   : ");
    Serial.println(transactionSession.toRole);

    Serial.print("AMT  : ");
    Serial.println(transactionSession.amount);

    Serial.println("WAITING SENDER NFC");
    Serial.println("===============================");
}