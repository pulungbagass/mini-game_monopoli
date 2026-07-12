#include "ws_property_broadcast.h"

#include "../../repositories/monopoly_repository.h"
#include "../../data/property_ownership_service.h"
#include "../../services/property_service.h"

#include "../ws_manager.h"

#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>

extern AsyncWebSocket ws;

/* ======================================================
   Broadcast Single Property
====================================================== */

void broadcastProperty(
    const String& assetId)
{
    JsonObject asset =
        getAssetById(assetId);

    if (asset.isNull())
        return;

    PropertyOwnership* property =
        getOwnership(assetId);

    if (property == nullptr)
        return;

    JsonDocument doc;

    doc["type"] = "property_update";

    doc["assetId"] =
        assetId;

    doc["owner"] =
        property->ownerRole;

    doc["owned"] =
        property->owned;

    doc["mortgaged"] =
        property->mortgaged;

    doc["house"] =
        property->houseCount;

    doc["hotel"] =
        property->hotel;

    String response;

    serializeJson(
        doc,
        response);

    ws.textAll(
        response);
}

/* ======================================================
   Broadcast All Properties
====================================================== */

void broadcastAllProperties()
{
    JsonArray assets =
        getMonopolyRepository()["monopoly_assets"];

    JsonDocument doc;

    doc["type"] =
        "property_state";

    JsonArray list =
        doc["properties"]
            .to<JsonArray>();

    for (JsonObject asset : assets)
    {
        String assetId =
            asset["assets_id"]
                .as<String>();

        PropertyOwnership* property =
            getOwnership(assetId);

        if (property == nullptr)
            continue;

        JsonObject item =
            list.add<JsonObject>();

        item["assetId"] =
            assetId;

        item["owner"] =
            property->ownerRole;

        item["owned"] =
            property->owned;

        item["mortgaged"] =
            property->mortgaged;

        item["house"] =
            property->houseCount;

        item["hotel"] =
            property->hotel;
    }

    String response;

    serializeJson(
        doc,
        response);

    ws.textAll(
        response);
}