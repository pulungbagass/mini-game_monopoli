#include "ws_transaction.h"

#include "../../services/transaction_session_service.h"
#include "../../data/transaction_session.h"

#include <ArduinoJson.h>

extern AsyncWebSocket ws;

/* ======================================================
   WAIT SOURCE
====================================================== */

void sendTransactionWaitSource()
{
    JsonDocument doc;

    doc["type"] = "transaction_wait_source";

    String json;
    serializeJson(doc, json);

    ws.textAll(json);
}

/* ======================================================
   WAIT TARGET
====================================================== */

void sendTransactionWaitTarget()
{
    JsonDocument doc;

    doc["type"] = "transaction_wait_target";

    String json;
    serializeJson(doc, json);

    ws.textAll(json);
}

/* ======================================================
   SUCCESS
====================================================== */

void sendTransactionSuccess()
{
    JsonDocument doc;

    doc["type"] = "transaction_success";

    doc["fromRole"] =
        transactionSession.sourceRole;

    doc["toRole"] =
        transactionSession.targetRole;

    doc["amount"] =
        transactionSession.amount;

    String json;
    serializeJson(doc, json);

    ws.textAll(json);
}

/* ======================================================
   FAILED
====================================================== */

void sendTransactionFailed()
{
    JsonDocument doc;

    doc["type"] = "transaction_failed";

    doc["fromRole"] =
        transactionSession.sourceRole;

    doc["toRole"] =
        transactionSession.targetRole;

    doc["amount"] =
        transactionSession.amount;

    String json;
    serializeJson(doc, json);

    ws.textAll(json);
}

/* ======================================================
   TIMEOUT
====================================================== */

void sendTransactionTimeout()
{
    JsonDocument doc;

    doc["type"] = "transaction_timeout";

    doc["fromRole"] =
        transactionSession.sourceRole;

    doc["toRole"] =
        transactionSession.targetRole;

    doc["amount"] =
        transactionSession.amount;

    String json;
    serializeJson(doc, json);

    ws.textAll(json);
}

/* ======================================================
   HANDLE TRANSACTION
====================================================== */

void handleTransaction(
    AsyncWebSocketClient *client,
    JsonDocument &doc
)
{
    String fromRole =
        doc["fromRole"];

    String toRole =
        doc["toRole"];

    int amount =
        doc["amount"];

    JsonDocument response;

    if (!startTransaction(
        TRANSACTION_TRANSFER,
        PROPERTY_NONE,
        fromRole,
        toRole,
        "",
        amount))
    {
        response["type"] =
            "transaction_busy";
    }
    else
    {
        response["type"] =
            "transfer_wait_sender";
    }

    String json;
    serializeJson(response, json);

    ws.text(
        client->id(),
        json
    );
}