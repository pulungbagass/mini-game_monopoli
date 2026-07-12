#pragma once

#include <Arduino.h>

// ======================================================
// Claim Event
// ======================================================

void eventClaimSuccess(
    const String& role,
    const String& deviceId
);

void eventClaimFailed();

// ======================================================
// Transaction Event
// ======================================================

void eventTransactionSuccess();

void eventTransactionFailed();

/* ======================================================
   Property Event
====================================================== */

void eventPropertyBought(
    const String& assetId
);

void eventPropertySold(
    const String& assetId
);

void eventPropertyTransferred(
    const String& assetId
);

void eventPropertyMortgaged(
    const String& assetId
);

void eventPropertyReleased(
    const String& assetId
);

void eventHouseBuilt(
    const String& assetId
);

void eventHouseSold(
    const String& assetId
);

void eventHotelBuilt(
    const String& assetId
);

void eventHotelSold(
    const String& assetId
);

void eventPropertyReset(
    const String& assetId
);