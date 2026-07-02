#include "ws_transaction_cancel.h"

#include "../../services/transaction_session_service.h"

#include "../../websocket/handlers/ws_transaction.h"
#include "../../websocket/ws_manager.h"

#include <ArduinoJson.h>

/* ======================================================
   CANCEL TRANSACTION
====================================================== */

void handleTransactionCancel(
    AsyncWebSocketClient *client,
    JsonDocument &doc
)
{
    if(!isTransactionActive())
    {
        JsonDocument res;

        res["type"] = "transaction_failed";
        res["reason"] = "no_active_transaction";

        String json;

        serializeJson(res,json);

        client->text(json);

        return;
    }

    cancelTransaction();

    JsonDocument res;

    res["type"] = "transaction_cancelled";

    String json;

    serializeJson(res,json);

    client->text(json);

    ws.textAll(json);

    Serial.println();
    Serial.println("TRANSACTION CANCELLED");
}