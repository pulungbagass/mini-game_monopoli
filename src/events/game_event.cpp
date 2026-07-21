#include "game_event.h"

#include "../notification/notification.h"

// websocket
#include "../websocket/handlers/ws_broadcast.h"
#include "../websocket/handlers/ws_property_broadcast.h"

// data / lookup helpers
#include "../data/game_log.h"
#include "../data/property_ownership_service.h"
#include "../services/property_service.h"

// logger
// nanti

// oled
// nanti

/* ======================================================
   HELPER: nama properti untuk pesan log
====================================================== */

static String assetName(const String& assetId)
{
    if (assetId == "")
        return "";

    JsonObject asset = getAssetById(assetId);

    if (asset.isNull())
        return assetId;

    return asset["asset_name"].as<String>();
}

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

    notifyClaimSuccess();

    Serial.println(
        "[EVENT] CLAIM SUCCESS"
    );
}

// ======================================================

void eventClaimFailed()
{
    notifyClaimFailed();

    Serial.println(
        "[EVENT] CLAIM FAILED"
    );
}

// ======================================================

void eventTransactionSuccess()
{
    notifyTransactionSuccess();

    broadcastGameState();

    Serial.println(
        "[EVENT] TRANSACTION SUCCESS"
    );
}

// ======================================================

void eventTransactionFailed()
{
    notifyTransactionFailed();

    Serial.println(
        "[EVENT] TRANSACTION FAILED"
    );
}

// ======================================================

void eventMoneyTransferred(
    const String& fromRole,
    const String& toRole,
    int amount
)
{
    notifyTransactionSuccess();

    broadcastGameState();

    String msg =
        fromRole + " mentransfer $" + String(amount) +
        " ke " + toRole;

    addGameLog(
        LOG_MONEY_OUT,
        msg,
        fromRole,
        toRole
    );

    Serial.println("[EVENT] MONEY TRANSFERRED");
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

    String buyerRole = "";
    PropertyOwnership* ownership = getOwnership(assetId);
    if (ownership != nullptr)
        buyerRole = ownership->ownerRole;

    int price = getPurchasePrice(assetId);

    String msg =
        buyerRole + " membeli " + assetName(assetId) +
        " seharga $" + String(price);

    addGameLog(LOG_PROPERTY, msg, buyerRole, "BANK");

    Serial.println(
        "[EVENT] PROPERTY BOUGHT");
}

/* ======================================================
   PROPERTY SELL
====================================================== */

void eventPropertySold(
    const String& assetId,
    const String& sellerRole)
{
    notifyTransactionSuccess();

    broadcastProperty(assetId);
    broadcastGameState();

    String msg =
        sellerRole + " menjual " + assetName(assetId) +
        " ke Bank";

    addGameLog(LOG_PROPERTY, msg, sellerRole, "BANK");

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

    String newOwnerRole = "";
    PropertyOwnership* ownership = getOwnership(assetId);
    if (ownership != nullptr)
        newOwnerRole = ownership->ownerRole;

    String msg =
        assetName(assetId) + " dipindahkan kepemilikannya ke " +
        newOwnerRole;

    addGameLog(LOG_PROPERTY, msg, newOwnerRole, "");

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

    String ownerRole = "";
    PropertyOwnership* ownership = getOwnership(assetId);
    if (ownership != nullptr)
        ownerRole = ownership->ownerRole;

    String msg =
        ownerRole + " menggadaikan " + assetName(assetId);

    addGameLog(LOG_PROPERTY, msg, ownerRole, "BANK");

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

    String ownerRole = "";
    PropertyOwnership* ownership = getOwnership(assetId);
    if (ownership != nullptr)
        ownerRole = ownership->ownerRole;

    String msg =
        ownerRole + " menebus gadai " + assetName(assetId);

    addGameLog(LOG_PROPERTY, msg, ownerRole, "BANK");

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

    String ownerRole = "";
    PropertyOwnership* ownership = getOwnership(assetId);
    if (ownership != nullptr)
        ownerRole = ownership->ownerRole;

    String msg =
        ownerRole + " membangun rumah di " + assetName(assetId);

    addGameLog(LOG_PROPERTY, msg, ownerRole, "BANK");

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

    String ownerRole = "";
    PropertyOwnership* ownership = getOwnership(assetId);
    if (ownership != nullptr)
        ownerRole = ownership->ownerRole;

    String msg =
        ownerRole + " menjual rumah di " + assetName(assetId);

    addGameLog(LOG_PROPERTY, msg, ownerRole, "BANK");

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

    String ownerRole = "";
    PropertyOwnership* ownership = getOwnership(assetId);
    if (ownership != nullptr)
        ownerRole = ownership->ownerRole;

    String msg =
        ownerRole + " membangun hotel di " + assetName(assetId);

    addGameLog(LOG_PROPERTY, msg, ownerRole, "BANK");

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

    String ownerRole = "";
    PropertyOwnership* ownership = getOwnership(assetId);
    if (ownership != nullptr)
        ownerRole = ownership->ownerRole;

    String msg =
        ownerRole + " menjual hotel di " + assetName(assetId);

    addGameLog(LOG_PROPERTY, msg, ownerRole, "BANK");

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

/* ======================================================
   RENT PAID
====================================================== */

void eventRentPaid(
    const String& assetId,
    const String& payerRole,
    const String& ownerRole,
    int amount)
{
    notifyTransactionSuccess();

    broadcastGameState();

    String msg =
        payerRole + " membayar sewa $" + String(amount) +
        " ke " + ownerRole + " (" + assetName(assetId) + ")";

    addGameLog(LOG_MONEY_OUT, msg, payerRole, ownerRole);

    Serial.println("[EVENT] RENT PAID");
}

/* ======================================================
   CARD DRAWN (CHANCE / COMMUNITY CHEST)
====================================================== */

void eventCardDrawn(
    const String& deckName,
    const String& role,
    const String& cardText)
{
    notifyTransactionSuccess();

    String msg =
        role + " mengambil kartu " + deckName + ": " + cardText;

    addGameLog(LOG_CARD, msg, role, "");

    Serial.println("[EVENT] CARD DRAWN");
}

/* ======================================================
   AUCTION EVENTS
====================================================== */

void eventAuctionStarted(
    const String& assetId)
{
    String msg =
        "Bank memulai lelang untuk " + assetName(assetId);

    addGameLog(LOG_AUCTION, msg, "BANK", "");

    Serial.println("[EVENT] AUCTION STARTED");
}

void eventAuctionBid(
    const String& role,
    int newHighestBid)
{
    String msg =
        role + " menaikkan taruhan menjadi $" + String(newHighestBid);

    addGameLog(LOG_AUCTION, msg, role, "");

    Serial.println("[EVENT] AUCTION BID");
}

void eventAuctionEnded(
    const String& assetId,
    const String& winnerRole,
    int winningBid)
{
    broadcastGameState();

    String msg;

    if (winnerRole == "")
    {
        msg = "Lelang " + assetName(assetId) +
              " berakhir tanpa pemenang";
    }
    else
    {
        msg = winnerRole + " memenangkan lelang " +
              assetName(assetId) + " seharga $" +
              String(winningBid);
    }

    addGameLog(LOG_AUCTION, msg, winnerRole, "BANK");

    Serial.println("[EVENT] AUCTION ENDED");
}
