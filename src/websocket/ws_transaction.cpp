#include "ws_transaction.h"

#include "../services/transaction_session_service.h"

#include <ArduinoJson.h>

extern AsyncWebSocket ws;

/* ======================================================
   HANDLE TRANSACTION
====================================================== */

void handleTransaction(
    AsyncWebSocketClient *client,
    JsonDocument &doc
)
{
    String fromRole = doc["fromRole"];
    String toRole   = doc["toRole"];

    int amount = doc["amount"];

    JsonDocument response;

    if (!startTransaction(
            fromRole,
            toRole,
            amount))
    {
        response["type"] = "transaction_busy";
    }
    else
    {
        response["type"] = "transfer_wait_sender";
    }

    String json;

    serializeJson(response, json);

    ws.text(
        client->id(),
        json
    );
}