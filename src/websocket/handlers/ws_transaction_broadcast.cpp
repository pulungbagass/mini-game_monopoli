#include "ws_transaction_broadcast.h"
#include "../ws_manager.h"
#include "../../data/transaction_session.h"

#include <ArduinoJson.h>

extern AsyncWebSocket ws;

/* ======================================================
   TRANSACTION STATE
====================================================== */

void sendTransactionState(
    const String& type
)
{
    JsonDocument doc;

    doc["type"] =
        type;

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