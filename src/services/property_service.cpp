#include "property_service.h"

#include "../repositories/monopoly_repository.h"

JsonObject getAssetById(const String& assetId)
{
    JsonArray assets =
        getMonopolyRepository()["monopoly_assets"];

    for(JsonObject asset : assets)
    {
        if(asset["assets_id"] == assetId)
        {
            return asset;
        }
    }

    return JsonObject();
}

bool isBuyable(const String& assetId)
{
    JsonObject asset =
        getAssetById(assetId);

    if(asset.isNull())
        return false;

    return asset["action"]["buyable"];
}

int getPurchasePrice(const String& assetId)
{
    JsonObject asset =
        getAssetById(assetId);

    if(asset.isNull())
        return -1;

    return asset["purchase_price"];
}

int getMortgageValue(const String& assetId)
{
    JsonObject asset =
        getAssetById(assetId);

    if(asset.isNull())
        return -1;

    return asset["mortgage"]["value"];
}

int getReleaseCost(const String& assetId)
{
    JsonObject asset =
        getAssetById(assetId);

    if(asset.isNull())
        return -1;

    return asset["mortgage"]["release_cost"];
}

JsonObject getRentData(const String& assetId)
{
    JsonObject asset =
        getAssetById(assetId);

    if(asset.isNull())
        return JsonObject();

    return asset["rent"];
}

JsonObject getDevelopmentCost(const String& assetId)
{
    JsonObject asset =
        getAssetById(assetId);

    if(asset.isNull())
        return JsonObject();

    return asset["development_cost"];
}