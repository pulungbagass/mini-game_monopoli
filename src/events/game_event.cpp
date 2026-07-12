#include "game_event.h"

#include "../notification/notification.h"

// websocket
#include "../websocket/handlers/ws_broadcast.h"
#include "../websocket/handlers/ws_property_broadcast.h"

// logger
// nanti

// oled
// nanti

// ======================================================

void eventClaimSuccess(
    const String& role,
    const String& deviceId
)
{
    sendAccessGranted(
        role,
        deviceId
    );

    // TODO:
    // Logger
    // OLED
    // Analytics
    notifyClaimSuccess();

    Serial.println(
        "[EVENT] CLAIM SUCCESS"
    );
}

// ======================================================

void eventClaimFailed()
{
    notifyClaimFailed();

    // TODO:
    // Logger
    // OLED
    // Analytics

    Serial.println(
        "[EVENT] CLAIM FAILED"
    );
}

// ======================================================

void eventTransactionSuccess()
{
    notifyTransactionSuccess();

    broadcastGameState();

    // TODO:
    // Logger
    // OLED
    // Analytics
    Serial.println(
        "[EVENT] TRANSACTION SUCCESS"
    );
}

// ======================================================

void eventTransactionFailed()
{
    notifyTransactionFailed();

    // TODO:
    // Logger
    // OLED
    // Analytics
    Serial.println(
        "[EVENT] TRANSACTION FAILED"
    );
}

// =========================================================

/* ======================================================
   PROPERTY BUY
====================================================== */

void eventPropertyBought(
    const String& assetId)
{
    notifyTransactionSuccess();

    broadcastProperty(assetId);
    broadcastGameState();

    Serial.println(
        "[EVENT] PROPERTY BOUGHT");
}

/* ======================================================
   PROPERTY SELL
====================================================== */

void eventPropertySold(
    const String& assetId)
{
    notifyTransactionSuccess();

    broadcastProperty(assetId);
    broadcastGameState();

    Serial.println(
        "[EVENT] PROPERTY SOLD");
}

/* ======================================================
   PROPERTY TRANSFER
====================================================== */

void eventPropertyTransferred(
    const String& assetId)
{
    notifyTransactionSuccess();

    broadcastProperty(assetId);
    broadcastGameState();

    Serial.println(
        "[EVENT] PROPERTY TRANSFERRED");
}

/* ======================================================
   MORTGAGE
====================================================== */

void eventPropertyMortgaged(
    const String& assetId)
{
    notifyTransactionSuccess();

    broadcastProperty(assetId);
    broadcastGameState();

    Serial.println(
        "[EVENT] PROPERTY MORTGAGED");
}

/* ======================================================
   RELEASE
====================================================== */

void eventPropertyReleased(
    const String& assetId)
{
    notifyTransactionSuccess();

    broadcastProperty(assetId);
    broadcastGameState();

    Serial.println(
        "[EVENT] PROPERTY RELEASED");
}

/* ======================================================
   HOUSE BUILT
====================================================== */

void eventHouseBuilt(
    const String& assetId)
{
    notifyTransactionSuccess();

    broadcastProperty(assetId);
    broadcastGameState();

    Serial.println(
        "[EVENT] HOUSE BUILT");
}

/* ======================================================
   HOUSE SOLD
====================================================== */

void eventHouseSold(
    const String& assetId)
{
    notifyTransactionSuccess();

    broadcastProperty(assetId);
    broadcastGameState();

    Serial.println(
        "[EVENT] HOUSE SOLD");
}

/* ======================================================
   HOTEL BUILT
====================================================== */

void eventHotelBuilt(
    const String& assetId)
{
    notifyTransactionSuccess();

    broadcastProperty(assetId);
    broadcastGameState();

    Serial.println(
        "[EVENT] HOTEL BUILT");
}

/* ======================================================
   HOTEL SOLD
====================================================== */

void eventHotelSold(
    const String& assetId)
{
    notifyTransactionSuccess();

    broadcastProperty(assetId);
    broadcastGameState();

    Serial.println(
        "[EVENT] HOTEL SOLD");
}

/* ======================================================
   PROPERTY RESET
====================================================== */

void eventPropertyReset(
    const String& assetId)
{
    notifyTransactionSuccess();

    broadcastProperty(assetId);
    broadcastGameState();

    Serial.println(
        "[EVENT] PROPERTY RESET");
}