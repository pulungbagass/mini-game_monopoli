#pragma once

#include <Arduino.h>

#include "../data/property_ownership_data.h"

/* ======================================================
   Initialization
====================================================== */

void initPropertyOwnership();

void resetPropertyOwnership();

/* ======================================================
   Getter
====================================================== */

PropertyOwnership* getOwnership(
    const String& assetId
);

bool hasOwner(
    const String& assetId
);

String getOwnerProperty(
    const String& assetId
);

bool isOwnedBy(
    const String& assetId,
    const String& role
);

bool isMortgaged(
    const String& assetId
);

uint8_t getHouseCount(
    const String& assetId
);

bool hasHotel(
    const String& assetId
);

bool isDeveloped(
    const String& assetId
);

/* ======================================================
   Ownership
====================================================== */

bool setOwner(
    const String& assetId,
    const String& role
);

bool transferOwnership(
    const String& assetId,
    const String& newOwner
);

bool clearOwner(
    const String& assetId
);

/* ======================================================
   Monopoly
====================================================== */

bool ownsColorGroup(
    const String& role,
    const String& colorGroup
);

/* ======================================================
   Mortgage
====================================================== */

bool setMortgage(
    const String& assetId,
    bool state
);

/* ======================================================
   Building State
====================================================== */

bool buildHouseState(
    const String& assetId
);

bool sellHouseState(
    const String& assetId
);

bool buildHotelState(
    const String& assetId
);

bool sellHotelState(
    const String& assetId
);

bool resetDevelopment(
    const String& assetId
);

/* ======================================================
   Statistics
====================================================== */

int countOwnedProperties(
    const String& role
);

int countOwnedColorGroup(
    const String& role,
    const String& colorGroup
);

int countOwnedRailroad(
    const String& role
);

int countOwnedUtility(
    const String& role
);

/* ======================================================
   Validation
====================================================== */

bool canBuyPropertyState(
    const String& assetId
);

bool canSellPropertyState(
    const String& assetId
);

bool canTransferPropertyState(
    const String& assetId
);

bool canBuildHouseState(
    const String& assetId
);

bool canSellHouseState(
    const String& assetId
);

bool canBuildHotelState(
    const String& assetId
);

bool canSellHotelState(
    const String& assetId
);

bool canMortgageState(
    const String& assetId
);

bool canReleaseMortgageState(
    const String& assetId
);

/* ======================================================
   Rent Validation
====================================================== */

bool canPayRentState(
    const String& assetId
);

bool canReceiveRentState(
    const String& assetId
);