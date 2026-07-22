#include "property_transaction_service.h"

#include "../data/property_ownership_service.h"
#include "../data/transaction_session.h"
#include "../events/game_event.h"


#include "property_service.h"
#include "transaction_service.h"

/* ======================================================
   Calculate Build Cost
====================================================== */

int calculateBuildCost(
    const String& assetId,
    bool hotel
)
{
    JsonObject development =
        getDevelopmentCost(assetId);

    if (development.isNull())
        return 0;

    return hotel
        ? development["hotel_cost"] | 0
        : development["house_cost"] | 0;
}



/* ======================================================
   Calculate Rent
====================================================== */

int calculateRent(
    const String& assetId,
    int diceValue
)
{
    JsonObject asset =
        getAssetById(assetId);

    if (asset.isNull())
        return 0;

    PropertyOwnership* ownership =
        getOwnership(assetId);

    if (ownership == nullptr)
        return 0;

    if (!ownership->owned)
        return 0;

    String ownerRole =
        ownership->ownerRole;

    String type =
        asset["type"].as<String>();

    /* ==========================================
       Property
    ========================================== */

    if (type == "Property")
    {
        JsonObject rent =
            asset["rent"];

        if (ownership->hotel)
            return rent["hotel"] | 0;

        switch (ownership->houseCount)
        {
            case 4:
                return rent["house4"] | 0;

            case 3:
                return rent["house3"] | 0;

            case 2:
                return rent["house2"] | 0;

            case 1:
                return rent["house1"] | 0;
        }

        String colorGroup =
            asset["color_group"].as<String>();

        if (ownsColorGroup(
                ownerRole,
                colorGroup))
        {
            return rent["monopoly_set"] | 0;
        }

        return rent["base"] | 0;
    }

    /* ==========================================
       Railroad
    ========================================== */

    if (type == "Railroad")
    {
        JsonObject rent =
            asset["rent"];

        int owned =
            countOwnedRailroad(ownerRole);

        switch (owned)
        {
            case 4:
                return rent["owned4"] | 0;

            case 3:
                return rent["owned3"] | 0;

            case 2:
                return rent["owned2"] | 0;

            case 1:
                return rent["owned1"] | 0;
        }

        return 0;
    }

    /* ==========================================
       Utility
    ========================================== */

    if (type == "Utility")
    {
        int owned =
            countOwnedUtility(ownerRole);

        return (owned >= 2)
            ? diceValue * 10
            : diceValue * 4;
    }

    return 0;
}

/* ======================================================
   Buy Property
====================================================== */

bool buyProperty(
    const String& assetId,
    const String& buyerRole
)
{
    /* ==========================================
       Step 1 : Validate Property
    ========================================== */

    if (!isBuyable(assetId))
        return false;

    if (!canBuyPropertyState(assetId))
        return false;

    /* ==========================================
       Step 2 : Validate Buyer
    ========================================== */

    if (!playerExists(buyerRole))
        return false;

    /* ==========================================
       Step 3 : Get Purchase Price
    ========================================== */

    int price =
        getPurchasePrice(assetId);

    if (price <= 0)
        return false;

    /* ==========================================
       Step 4 : Deduct Buyer Money
    ========================================== */

    if (!deductMoney(
            buyerRole,
            price))
    {
        return false;
    }

    /* ==========================================
       Step 5 : Set Property Owner
    ========================================== */

    if (!setOwner(
            assetId,
            buyerRole))
    {
        addMoney(
            buyerRole,
            price);

        return false;
    }

    eventPropertyBought(assetId);

    /* ==========================================
       Step 6 : Success
    ========================================== */

    return true;
}

/* ======================================================
   Pay Rent
====================================================== */

bool payRent(
    const String& payerRole,
    const String& assetId,
    int diceValue
)
{
    if (!canPayRentState(assetId))
    return false;

    /* ==========================================
       Step 1 : Validate Player
    ========================================== */

    if (!playerExists(payerRole))
        return false;

    /* ==========================================
       Step 2 : Validate Asset
    ========================================== */

    JsonObject asset =
        getAssetById(assetId);

    if (asset.isNull())
        return false;

    /* ==========================================
       Step 3 : Validate Ownership
    ========================================== */

    PropertyOwnership* ownership =
        getOwnership(assetId);

    if (ownership == nullptr)
        return false;

    String ownerRole =
        ownership->ownerRole;

    /* ==========================================
       Step 4 : Owner Cannot Pay Himself
    ========================================== */

    if (ownerRole == payerRole)
        return false;

    /* ==========================================
       Step 5 : Calculate Rent
    ========================================== */

    int rent =
        calculateRent(
            assetId,
            diceValue);

    if (rent <= 0)
        return false;

    /* ==========================================
       Step 6 : Transfer Money
    ========================================== */

    if (!transferMoney(
            payerRole,
            ownerRole,
            rent))
    {
        return false;
    }

    /* ==========================================
       Step 7 : Success
    ========================================== */

    // FIX (Phase 1 audit): payRent tidak pernah memicu event
    // sama sekali, jadi pembayaran sewa tidak muncul di
    // GAME LOG / broadcast game state secara instan.
    eventRentPaid(assetId, payerRole, ownerRole, rent);

    return true;
}

/* ======================================================
   Mortgage Property
====================================================== */

bool mortgageProperty(
    const String& assetId
)
{
    /* ==========================================
       Step 1 : Validate Property
    ========================================== */

    if (!canMortgageState(assetId))
        return false;

    /* ==========================================
       Step 2 : Get Ownership
    ========================================== */

    PropertyOwnership* ownership =
        getOwnership(assetId);

    if (ownership == nullptr)
        return false;

    /* ==========================================
       Step 3 : Get Mortgage Value
    ========================================== */

    int mortgageValue =
        getMortgageValue(assetId);

    if (mortgageValue <= 0)
        return false;

    /* ==========================================
       Step 4 : Give Money to Owner
    ========================================== */

    if (!addMoney(
            ownership->ownerRole,
            mortgageValue))
    {
        return false;
    }

    /* ==========================================
       Step 5 : Set Mortgage
    ========================================== */

    if (!setMortgage(
            assetId,
            true))
    {
        // Rollback Money

        deductMoney(
            ownership->ownerRole,
            mortgageValue);

        return false;
    }

    /* ==========================================
       Step 6 : Success
    ========================================== */

    eventPropertyMortgaged(assetId);

    return true;
}

/* ======================================================
   Release Mortgage
====================================================== */

bool releaseMortgage(
    const String& assetId
)
{
    /* ==========================================
       Step 1 : Validate Property
    ========================================== */

    if (!canReleaseMortgageState(assetId))
        return false;

    /* ==========================================
       Step 2 : Get Ownership
    ========================================== */

    PropertyOwnership* ownership =
        getOwnership(assetId);

    if (ownership == nullptr)
        return false;

    /* ==========================================
       Step 3 : Get Release Cost
    ========================================== */

    int releaseCost =
        getReleaseCost(assetId);

    if (releaseCost <= 0)
        return false;

    /* ==========================================
       Step 4 : Deduct Owner Money
    ========================================== */

    if (!deductMoney(
            ownership->ownerRole,
            releaseCost))
    {
        return false;
    }

    /* ==========================================
       Step 5 : Remove Mortgage
    ========================================== */

    if (!setMortgage(
            assetId,
            false))
    {
        // Rollback Money

        addMoney(
            ownership->ownerRole,
            releaseCost);

        return false;
    }

    /* ==========================================
       Step 6 : Success
    ========================================== */

    eventPropertyReleased(assetId);

    return true;
}


/* ======================================================
   Build House
====================================================== */

bool buildHouse(
    const String& assetId
)
{
    /* ==========================================
       Step 1 : Validate Property
    ========================================== */

    if (!canBuildHouseState(assetId))
        return false;

    /* ==========================================
       Step 2 : Get Ownership
    ========================================== */

    PropertyOwnership* ownership =
        getOwnership(assetId);

    if (ownership == nullptr)
        return false;

    /* ==========================================
       Step 3 : Get Build Cost
    ========================================== */

    int cost =
        calculateBuildCost(assetId);

    if (cost <= 0)
        return false;

    /* ==========================================
       Step 4 : Deduct Owner Money
    ========================================== */

    if (!deductMoney(
            ownership->ownerRole,
            cost))
    {
        return false;
    }

    /* ==========================================
       Step 5 : Build House
    ========================================== */

    if (!buildHouseState(assetId))
    {
        // Rollback Money

        addMoney(
            ownership->ownerRole,
            cost);

        return false;
    }

    /* ==========================================
       Step 6 : Success
    ========================================== */

    eventHouseBuilt(assetId);

    return true;
}

/* ======================================================
   Sell House
====================================================== */

bool sellHouse(
    const String& assetId
)
{
    /* ==========================================
       Step 1 : Validate
    ========================================== */

    if (!canSellHouseState(assetId))
        return false;

    /* ==========================================
       Step 2 : Get Ownership
    ========================================== */

    PropertyOwnership* ownership =
        getOwnership(assetId);

    if (ownership == nullptr)
        return false;

    /* ==========================================
       Step 3 : Calculate Refund
    ========================================== */

    int refund =
        calculateSellHouseRefund(assetId);

    if (refund <= 0)
        return false;

    /* ==========================================
       Step 4 : Sell House
    ========================================== */

    if (!sellHouseState(assetId))
        return false;

    /* ==========================================
       Step 5 : Give Money
    ========================================== */

    if (!addMoney(
            ownership->ownerRole,
            refund))
    {
        // Rollback

        buildHouseState(assetId);

        return false;
    }

    /* ==========================================
       Step 6 : Success
    ========================================== */

    eventHouseSold(assetId);

    return true;
}

/* ======================================================
   Build Hotel
====================================================== */

bool buildHotel(
    const String& assetId
)
{
    /* ==========================================
       Step 1 : Validate Property
    ========================================== */

    if (!canBuildHotelState(assetId))
        return false;

    /* ==========================================
       Step 2 : Get Ownership
    ========================================== */

    PropertyOwnership* ownership =
        getOwnership(assetId);

    if (ownership == nullptr)
        return false;

    /* ==========================================
       Step 3 : Get Hotel Cost
    ========================================== */

    int cost =
        calculateBuildCost(
            assetId,
            true
        );

    if (cost <= 0)
        return false;

    /* ==========================================
       Step 4 : Deduct Owner Money
    ========================================== */

    if (!deductMoney(
            ownership->ownerRole,
            cost))
    {
        return false;
    }

    /* ==========================================
       Step 5 : Build Hotel
    ========================================== */

    if (!buildHotelState(assetId))
    {
        // Rollback Money

        addMoney(
            ownership->ownerRole,
            cost);

        return false;
    }

    /* ==========================================
       Step 6 : Success
    ========================================== */

    eventHotelBuilt(assetId);

    return true;
}

/* ======================================================
   Sell Hotel
====================================================== */

bool sellHotel(
    const String& assetId
)
{

    if (!canSellHotelState(assetId))
        return false;

    /* ==========================================
       Step 1 : Get Ownership
    ========================================== */

    PropertyOwnership* ownership =
        getOwnership(assetId);

    if (ownership == nullptr)
        return false;

    /* ==========================================
       Step 2 : Get Sell Value
    ========================================== */

    int value =
        calculateSellHotelRefund(assetId);

    if (value <= 0)
        return false;

    /* ==========================================
       Step 3 : Sell Hotel
    ========================================== */

    if (!sellHotelState(assetId))
        return false;

    /* ==========================================
       Step 4 : Give Money
    ========================================== */

    if (!addMoney(
            ownership->ownerRole,
            value))
    {
        // Rollback

        buildHotelState(assetId);

        return false;
    }

    /* ==========================================
       Step 5 : Success
    ========================================== */

    eventHotelSold(assetId);

    return true;
}

/* ======================================================
   Sell Property
====================================================== */

bool sellProperty(
    const String& assetId,
    const String& ownerRole)
{

    if (!canSellPropertyState(assetId))
    return false;

    if (!playerExists(ownerRole))
        return false;

    if (!isOwnedBy(
            assetId,
            ownerRole))
    {
        return false;
    }

    PropertyOwnership* ownership =
        getOwnership(assetId);

    if (ownership == nullptr)
        return false;

    int sellValue =
        getSellValue(assetId);

    if (sellValue <= 0)
        return false;
    if (!clearOwner(assetId))
        return false;

    if (!addMoney(
            ownerRole,
            sellValue))
    {
        setOwner(
            assetId,
            ownerRole);
        return false;
    }

    eventPropertySold(assetId, ownerRole);

    return true;
}

PropertyState getPropertyState(
    const String& assetId)
{
    PropertyState state;
    PropertyOwnership* property =
        getOwnership(assetId);

    if(property == nullptr)
    {
        state.owned = false;
        state.mortgaged = false;
        state.houseCount = 0;
        state.hotel = false;
        state.ownerRole = "";
        return state;
    }

    state.owned =
        property->owned;
    state.mortgaged =
        property->mortgaged;
    state.houseCount =
        property->houseCount;
    state.hotel =
        property->hotel;
    state.ownerRole =
        property->ownerRole;
    return state;
}


bool transferProperty(
    const String& assetId,
    const String& newOwner)
{
    if(!playerExists(newOwner))
        return false;

    if(!canTransferPropertyState(assetId))
        return false;

    if (!transferOwnership(
        assetId,
        newOwner
    ))
    {
        return false;
    }

    // FIX (Phase 1 audit): dulu ada `return` sebelum baris
    // ini sehingga event & broadcast property_update tidak
    // pernah terkirim setelah transfer properti berhasil.
    eventPropertyTransferred(assetId);

    return true;
}

/* ======================================================
   Claim Auction Property
   (dipanggil dari PROPERTY_AUCTION_CLAIM saat pemenang
   lelang tap kartu NFC ke Bank)
====================================================== */

bool claimAuctionProperty(
    const String& assetId,
    const String& winnerRole
)
{
    /* ==========================================
       BUG FIX: dulu case ini memakai transferProperty(),
       yang mensyaratkan canTransferPropertyState()
       (property->owned == true). Properti hasil lelang
       BELUM punya owner, jadi validasi itu SELALU gagal
       dan transaksi "stuck" tanpa pernah sukses ataupun
       gagal dengan jelas.
    ========================================== */

    if (!isBuyable(assetId))
        return false;

    if (hasOwner(assetId))
        return false;

    if (!playerExists(winnerRole))
        return false;

    // Uang SUDAH dipotong otomatis di auction_service saat
    // lelang berakhir -> di sini TIDAK deductMoney lagi.
    if (!setOwner(assetId, winnerRole))
        return false;

    eventPropertyBought(assetId);

    return true;
}

bool clearPropertyOwnership(
    const String& assetId)
{
    return clearOwner(assetId);
}

bool destroyDevelopment(
    const String& assetId)
{
    return resetDevelopment(assetId);
}

bool propertyOwned(
    const String& assetId)
{
    return hasOwner(assetId);
}

int calculateSellValue(
    const String& assetId)
{
    return getSellValue(assetId);
}

int calculateReleaseCost(
    const String& assetId)
{
    return getReleaseCost(assetId);
}

int calculateSellHouseRefund(
    const String& assetId)
{
    return calculateBuildCost(assetId) / 2;
}

int calculateSellHotelRefund(
    const String& assetId)
{
    return calculateBuildCost(
        assetId,
        true
    ) / 2;
}