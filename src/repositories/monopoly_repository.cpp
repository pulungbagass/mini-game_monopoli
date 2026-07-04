#include "monopoly_repository.h"

#include <SPIFFS.h>


static JsonDocument monopolyDoc;

bool loadMonopolyRepository()
{
    File file = SPIFFS.open("/monopoly_rules.json", "r");

    if (!file)
        return false;

    DeserializationError err =
        deserializeJson(monopolyDoc, file);

    file.close();

    return !err;
}

JsonObject getAssetById(const String& assetId)
{
    JsonArray assets =
        monopolyDoc["monopoly_assets"];

    for (JsonObject asset : assets)
    {
        if (asset["assets_id"] == assetId)
            return asset;
    }

    return JsonObject();
}

JsonObject getAssetByName(const String& assetName)
{
    JsonArray assets =
        monopolyDoc["monopoly_assets"];

    for (JsonObject asset : assets)
    {
        if (asset["asset_name"] == assetName)
            return asset;
    }

    return JsonObject();
}

JsonObject getCornerByName(const String& cornerName)
{
    JsonArray corners =
        monopolyDoc["monopoly_corners"];

    for (JsonObject corner : corners)
    {
        if (corner["corner_name"] == cornerName)
            return corner;
    }

    return JsonObject();
}

JsonObject getTaxByName(const String& taxName)
{
    JsonArray taxes =
        monopolyDoc["monopoly_taxes"];

    for (JsonObject tax : taxes)
    {
        if (tax["tax_name"] == taxName)
            return tax;
    }

    return JsonObject();
}

JsonObject getChanceCard(int index)
{
    JsonArray cards =
        monopolyDoc["monopoly_chance"];

    if(index < 0 || index >= cards.size())
        return JsonObject();

    return cards[index];
}

JsonObject getCommunityChestCard(int index)
{
    JsonArray cards =
        monopolyDoc["monopoly_community_chest"];

    if(index < 0 || index >= cards.size())
        return JsonObject();

    return cards[index];
}

int getAssetCount()
{
    return monopolyDoc["monopoly_assets"].size();
}

int getChanceCount()
{
    return monopolyDoc["monopoly_chance"].size();
}

int getCommunityChestCount()
{
    return monopolyDoc["monopoly_community_chest"].size();
}