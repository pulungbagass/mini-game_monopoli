#pragma once

#include <Arduino.h>

#define TOTAL_PROPERTIES 28

struct PropertyOwnership
{
    String assetId;

    String ownerRole;

    bool owned;

    bool mortgaged;

    uint8_t houseCount;

    bool hotel;
};

extern PropertyOwnership propertyOwnership[TOTAL_PROPERTIES];