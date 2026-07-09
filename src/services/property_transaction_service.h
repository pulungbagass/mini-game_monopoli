#pragma once

#include <Arduino.h>

/* ======================================================
   Property Transaction
====================================================== */

bool buyProperty(
    const String& assetId,
    const String& buyerRole
);

bool payRent(
    const String& payerRole,
    const String& assetId,
    int diceValue = 0
);

/* ======================================================
   Mortgage
====================================================== */

bool mortgageProperty(
    const String& assetId
);

bool releaseMortgage(
    const String& assetId
);

/* ======================================================
   House
====================================================== */

bool buildHouse(
    const String& assetId
);

bool sellHouse(
    const String& assetId
);

/* ======================================================
   Hotel
====================================================== */

bool buildHotel(
    const String& assetId
);

bool sellHotel(
    const String& assetId
);

/* ======================================================
   Validation
====================================================== */

bool canBuildHouse(
    const String& assetId
);

bool canBuildHotel(
    const String& assetId
);

/* ======================================================
   Calculation
====================================================== */

int calculateRent(
    const String& assetId,
    int diceValue = 0
);

int calculateBuildCost(
    const String& assetId,
    bool hotel = false
);