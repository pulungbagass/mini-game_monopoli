#include "property_ownership_service.h"

#include "../repositories/monopoly_repository.h"
#include "../services/property_service.h"
#include "property_ownership_data.h"
#include "../events/game_event.h"


void initPropertyOwnership()
{
    JsonArray assets =
        getMonopolyRepository()["monopoly_assets"];

    int index = 0;

    for (JsonObject asset : assets)
    {
        if (index >= TOTAL_PROPERTIES)
            break;

        propertyOwnership[index].assetId =
            asset["assets_id"].as<String>();

        propertyOwnership[index].ownerRole = "";
        propertyOwnership[index].owned = false;
        propertyOwnership[index].mortgaged = false;
        propertyOwnership[index].houseCount = 0;
        propertyOwnership[index].hotel = false;

        index++;
    }
}

void resetPropertyOwnership()
{
    for (int i = 0; i < TOTAL_PROPERTIES; i++)
    {
        propertyOwnership[i].ownerRole = "";
        propertyOwnership[i].owned = false;
        propertyOwnership[i].mortgaged = false;
        propertyOwnership[i].houseCount = 0;
        propertyOwnership[i].hotel = false;
    }
    eventPropertyReset("");
}

PropertyOwnership* getOwnership(
    const String& assetId)
{
    for (int i = 0; i < TOTAL_PROPERTIES; i++)
    {
        if (propertyOwnership[i].assetId == assetId)
            return &propertyOwnership[i];
    }

    return nullptr;
}

bool hasOwner(
    const String& assetId)
{
    PropertyOwnership* property =
        getOwnership(assetId);

    return property != nullptr &&
           property->owned;
}

String getOwnerProperty(
    const String& assetId)
{
    PropertyOwnership* property =
        getOwnership(assetId);

    if (property == nullptr)
        return "";

    return property->ownerRole;
}

bool isOwnedBy(
    const String& assetId,
    const String& role)
{
    PropertyOwnership* property =
        getOwnership(assetId);

    if (property == nullptr)
        return false;

    return property->owned &&
           property->ownerRole == role;
}

bool isMortgaged(
    const String& assetId)
{
    PropertyOwnership* property =
        getOwnership(assetId);

    return property != nullptr &&
           property->mortgaged;
}

uint8_t getHouseCount(
    const String& assetId)
{
    PropertyOwnership* property =
        getOwnership(assetId);

    if (property == nullptr)
        return 0;

    return property->houseCount;
}

bool hasHotel(
    const String& assetId)
{
    PropertyOwnership* property =
        getOwnership(assetId);

    return property != nullptr &&
           property->hotel;
}

bool setOwner(
    const String& assetId,
    const String& role)
{
    PropertyOwnership* property =
        getOwnership(assetId);

    if (property == nullptr)
        return false;

    property->ownerRole = role;
    property->owned = true;

    return true;
}

bool transferOwnership(
    const String& assetId,
    const String& newOwner)
{
    PropertyOwnership* property =
        getOwnership(assetId);

    if (property == nullptr)
        return false;

    property->ownerRole = newOwner;
    property->owned = true;
    property->mortgaged = false;
    property->houseCount = 0;
    property->hotel = false;

    return true;
}

bool clearOwner(
    const String& assetId)
{
    PropertyOwnership* property =
        getOwnership(assetId);

    if (property == nullptr)
        return false;

    property->ownerRole = "";
    property->owned = false;
    property->mortgaged = false;
    property->houseCount = 0;
    property->hotel = false;

    return true;
}

bool ownsColorGroup(
    const String& role,
    const String& color_group)
{
    JsonArray assets =
        getMonopolyRepository()["monopoly_assets"];

    int total = 0;
    int owned = 0;

    for (JsonObject asset : assets)
    {
        if (asset["type"] != "Property")
            continue;

        if (asset["color_group"].as<String>() != color_group)
        continue;

        total++;

        if (isOwnedBy(
                asset["assets_id"].as<String>(),
                role))
        {
            owned++;
        }
    }

    return total > 0 &&
           total == owned;
}

bool setMortgage(
    const String& assetId,
    bool state)
{
    PropertyOwnership* property =
        getOwnership(assetId);

    if (property == nullptr)
        return false;

    property->mortgaged = state;

    return true;
}

bool buildHouseState(
    const String& assetId)
{
    PropertyOwnership* property =
        getOwnership(assetId);

    if (property == nullptr)
        return false;

    if (!property->owned)
        return false;

    if (property->mortgaged)
        return false;

    if (property->hotel)
        return false;

    if (property->houseCount >= 4)
        return false;

    property->houseCount++;

    return true;
}

bool sellHouseState(
    const String& assetId)
{
    PropertyOwnership* property =
        getOwnership(assetId);

    if (property == nullptr)
        return false;

    if (property->houseCount == 0)
        return false;

    property->houseCount--;

    return true;
}

bool buildHotelState(
    const String& assetId)
{
    PropertyOwnership* property =
        getOwnership(assetId);
    if(property == nullptr)
        return false;
    if(!property->owned)
        return false;
    if(property->mortgaged)
        return false;
    if(property->hotel)
        return false;
    if(property->houseCount != 4)
        return false;
    property->houseCount = 0;
    property->hotel = true;

    return true;
}

bool sellHotelState(
    const String& assetId)
{
    PropertyOwnership* property =
        getOwnership(assetId);

    if(property == nullptr)
        return false;

    if(!property->owned)
        return false;

    if(!property->hotel)
        return false;

    property->hotel = false;
    property->houseCount = 4;

    return true;
}

int countOwnedProperties(
    const String& role)
{
    int total = 0;

    for (int i = 0; i < TOTAL_PROPERTIES; i++)
    {
        if (propertyOwnership[i].owned &&
            propertyOwnership[i].ownerRole == role)
        {
            total++;
        }
    }

    return total;
}

int countOwnedColorGroup(
    const String& role,
    const String& color_group)
{
    JsonArray assets =
        getMonopolyRepository()["monopoly_assets"];

    int total = 0;

    for (JsonObject asset : assets)
    {
        if (asset["type"].as<String>() != "Property")
        continue;

        if (asset["color_group"].as<String>() != color_group)
        continue;

        if (isOwnedBy(
                asset["assets_id"].as<String>(),
                role))
        {
            total++;
        }
    }

    return total;
}

int countOwnedRailroad(
    const String& role)
{
    JsonArray assets =
        getMonopolyRepository()["monopoly_assets"];

    int total = 0;

    for (JsonObject asset : assets)
    {
        if (asset["type"] != "Railroad")
            continue;

        if (isOwnedBy(
                asset["assets_id"].as<String>(),
                role))
        {
            total++;
        }
    }

    return total;
}

int countOwnedUtility(
    const String& role)
{
    JsonArray assets =
        getMonopolyRepository()["monopoly_assets"];

    int total = 0;

    for (JsonObject asset : assets)
    {
        if (asset["type"] != "Utility")
            continue;

        if (isOwnedBy(
                asset["assets_id"].as<String>(),
                role))
        {
            total++;
        }
    }

    return total;
}

bool canBuyPropertyState(
    const String& assetId)
{
    if (!isBuyable(assetId))
        return false;

    return !hasOwner(assetId);
}

bool canBuildHouseState(
    const String& assetId)
{
    PropertyOwnership* property =
        getOwnership(assetId);

    if (property == nullptr)
        return false;

    if (!property->owned)
        return false;

    if (property->mortgaged)
        return false;

    if (property->hotel)
        return false;

    if (property->houseCount >= 4)
        return false;

    JsonObject asset =
        getAssetById(assetId);

    return ownsColorGroup(
        property->ownerRole,
        asset["color_group"].as<String>());
}

bool canBuildHotelState(
    const String& assetId)
{
    PropertyOwnership* property =
        getOwnership(assetId);

    if (property == nullptr)
        return false;

    if (!property->owned)
        return false;

    if (property->mortgaged)
        return false;

    if (property->hotel)
        return false;

    if (property->houseCount != 4)
        return false;

    JsonObject asset =
        getAssetById(assetId);

    return ownsColorGroup(
        property->ownerRole,
        asset["color_group"].as<String>());
}

bool canMortgageState(
    const String& assetId)
{
    PropertyOwnership* property =
        getOwnership(assetId);

    if (property == nullptr)
        return false;

    if (!property->owned)
        return false;

    if (property->mortgaged)
        return false;

    if (property->houseCount > 0)
        return false;

    if (property->hotel)
        return false;

    return true;
}

bool canReleaseMortgageState(
    const String& assetId)
{
    PropertyOwnership* property =
        getOwnership(assetId);

    if (property == nullptr)
        return false;

    return property->mortgaged;
}


bool canSellHouseState(
    const String& assetId)
{
    PropertyOwnership* property =
        getOwnership(assetId);

    if (property == nullptr)
        return false;

    if (!property->owned)
        return false;

    if (property->mortgaged)
        return false;

    if (property->houseCount <= 0)
        return false;

    if (property->hotel)
        return false;

    return true;
}

bool canSellHotelState(
    const String& assetId)
{
    PropertyOwnership* property =
        getOwnership(assetId);

    if (property == nullptr)
        return false;

    if (!property->owned)
        return false;

    if (property->mortgaged)
        return false;

    if (!property->hotel)
        return false;

    return true;
}

bool canSellPropertyState(
    const String& assetId)
{
    PropertyOwnership* property =
        getOwnership(assetId);

    if (property == nullptr)
        return false;

    if (!property->owned)
        return false;

    if (property->mortgaged)
        return false;

    if (property->houseCount > 0)
        return false;

    if (property->hotel)
        return false;

    return true;
}


bool canTransferPropertyState(
    const String& assetId)
{
    PropertyOwnership* property =
        getOwnership(assetId);

    if(property == nullptr)
        return false;

    if(!property->owned)
        return false;

    if(property->mortgaged)
        return false;

    if(property->houseCount > 0)
        return false;

    if(property->hotel)
        return false;

    return true;
}


bool canPayRentState(
    const String& assetId)
{
    PropertyOwnership* property =
        getOwnership(assetId);

    if(property == nullptr)
        return false;

    if(!property->owned)
        return false;

    if(property->mortgaged)
        return false;

    return true;
}

bool canReceiveRentState(
    const String& assetId)
{
    return canPayRentState(assetId);
}

bool isDeveloped(
    const String& assetId)
{
    PropertyOwnership* property =
        getOwnership(assetId);
    if(property == nullptr)
        return false;
    return property->houseCount > 0 ||
        property->hotel;
}

bool resetDevelopment(
    const String& assetId)
{
    PropertyOwnership* property =
        getOwnership(assetId);

    if(property == nullptr)
        return false;

    property->houseCount = 0;
    property->hotel = false;

    return true;
}