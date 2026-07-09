#include "ws_property.h"

#include "../../services/transaction_session_service.h"
#include "../../services/property_transaction_service.h"

#include <ArduinoJson.h>

extern AsyncWebSocket ws;

/* ======================================================
   HANDLE BUY PROPERTY
====================================================== */

void handleBuyProperty(
    AsyncWebSocketClient* client,
    JsonDocument& doc)
{
    String buyerRole =
        doc["buyerRole"];
    String assetId =
        doc["assetId"];
    JsonDocument response;

    if (!startTransaction(
            TRANSACTION_PROPERTY,
            PROPERTY_BUY,
            buyerRole,
            "",
            assetId,
            0))
    {
        response["type"] =
            "transaction_busy";
    }
    else
    {
        response["type"] =
            "property_wait_owner";
    }

    String json;
    serializeJson(response, json);
    ws.text(
        client->id(),
        json);
}

void handleSellProperty(
    AsyncWebSocketClient* client,
    JsonDocument& doc)
{
    String ownerRole =
        doc["ownerRole"];
    String assetId =
        doc["assetId"];
    JsonDocument response;

    if (!startTransaction(
            TRANSACTION_PROPERTY,
            PROPERTY_SELL,
            ownerRole,
            "",
            assetId,
            0))
    {
        response["type"] =
            "transaction_busy";
    }
    else
    {
        response["type"] =
            "property_wait_owner";
    }
    String json;
    serializeJson(response, json);
    ws.text(client->id(), json);
}

void handleMortgageProperty(
    AsyncWebSocketClient* client,
    JsonDocument& doc)
{
    String ownerRole =
        doc["ownerRole"];
    String assetId =
        doc["assetId"];
    JsonDocument response;

    if (!startTransaction(
            TRANSACTION_PROPERTY,
            PROPERTY_MORTGAGE,
            ownerRole,
            "",
            assetId,
            0))
    {
        response["type"] =
            "transaction_busy";
    }
    else
    {
        response["type"] =
            "property_wait_owner";
    }

    String json;
    serializeJson(response, json);
    ws.text(client->id(), json);
}

void handleReleaseMortgage(
    AsyncWebSocketClient* client,
    JsonDocument& doc)
{
    String ownerRole =
        doc["ownerRole"];
    String assetId =
        doc["assetId"];
    JsonDocument response;

    if (!startTransaction(
            TRANSACTION_PROPERTY,
            PROPERTY_RELEASE,
            ownerRole,
            "",
            assetId,
            0))
    {
        response["type"] =
            "transaction_busy";
    }
    else
    {
        response["type"] =
            "property_wait_owner";
    }
    String json;
    serializeJson(response, json);
    ws.text(client->id(), json);
}

void handleBuildHouse(
    AsyncWebSocketClient* client,
    JsonDocument& doc)
{
    String ownerRole =
        doc["ownerRole"];
    String assetId =
        doc["assetId"];
    JsonDocument response;

    if (!startTransaction(
            TRANSACTION_PROPERTY,
            PROPERTY_BUILD_HOUSE,
            ownerRole,
            "",
            assetId,
            0))
    {
        response["type"] =
            "transaction_busy";
    }
    else
    {
        response["type"] =
            "property_wait_owner";
    }
    String json;
    serializeJson(response, json);
    ws.text(client->id(), json);
}

void handleSellHouse(
    AsyncWebSocketClient* client,
    JsonDocument& doc)
{
    String ownerRole =
        doc["ownerRole"];
    String assetId =
        doc["assetId"];
    JsonDocument response;

    if (!startTransaction(
            TRANSACTION_PROPERTY,
            PROPERTY_SELL_HOUSE,
            ownerRole,
            "",
            assetId,
            0))
    {
        response["type"] =
            "transaction_busy";
    }
    else
    {
        response["type"] =
            "property_wait_owner";
    }
    String json;
    serializeJson(response, json);
    ws.text(client->id(), json);
}

void handleBuildHotel(
    AsyncWebSocketClient* client,
    JsonDocument& doc)
{
    String ownerRole =
        doc["ownerRole"];
    String assetId =
        doc["assetId"];
    JsonDocument response;

    if (!startTransaction(
            TRANSACTION_PROPERTY,
            PROPERTY_BUILD_HOTEL,
            ownerRole,
            "",
            assetId,
            0))
    {
        response["type"] =
            "transaction_busy";
    }
    else
    {
        response["type"] =
            "property_wait_owner";
    }
    String json;
    serializeJson(response, json);
    ws.text(client->id(), json);
}

void handleSellHotel(
    AsyncWebSocketClient* client,
    JsonDocument& doc)
{
    String ownerRole =
        doc["ownerRole"];
    String assetId =
        doc["assetId"];
    JsonDocument response;

    if (!startTransaction(
            TRANSACTION_PROPERTY,
            PROPERTY_SELL_HOTEL,
            ownerRole,
            "",
            assetId,
            0))
    {
        response["type"] =
            "transaction_busy";
    }
    else
    {
        response["type"] =
            "property_wait_owner";
    }
    String json;
    serializeJson(response, json);
    ws.text(client->id(), json);
}