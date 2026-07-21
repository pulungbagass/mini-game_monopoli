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

// New: dipakai transfer uang Player<->Player / Player<->Bank
// supaya masuk GLOBAL_LOG dengan nominal & pihak yang jelas.
void eventMoneyTransferred(
    const String& fromRole,
    const String& toRole,
    int amount
);

/* ======================================================
   Property Event
====================================================== */

void eventPropertyBought(
    const String& assetId
);

void eventPropertySold(
    const String& assetId,
    const String& sellerRole = ""
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

// New: bayar sewa (sebelumnya tidak ada event sama sekali)
void eventRentPaid(
    const String& assetId,
    const String& payerRole,
    const String& ownerRole,
    int amount
);

/* ======================================================
   Card Event (Chance / Community Chest)
====================================================== */

void eventCardDrawn(
    const String& deckName, // "CHANCE" | "COMMUNITY CHEST"
    const String& role,
    const String& cardText
);

/* ======================================================
   Auction Event
====================================================== */

void eventAuctionStarted(
    const String& assetId
);

void eventAuctionBid(
    const String& role,
    int newHighestBid
);

void eventAuctionEnded(
    const String& assetId,
    const String& winnerRole,
    int winningBid
);
