#include "property_transaction_executor.h"

#include "../data/transaction_session.h"
#include "../services/property_transaction_service.h"

bool executePropertyTransaction()
{
    bool success = false;

    switch (transactionSession.propertyAction)
    {
        case PROPERTY_BUY:

            success = buyProperty(
                transactionSession.assetId,
                transactionSession.sourceRole
            );

            break;

        case PROPERTY_PAY_RENT:

            success = payRent(
                transactionSession.sourceRole,
                transactionSession.assetId,
                transactionSession.amount
            );

            break;

        case PROPERTY_MORTGAGE:

            success = mortgageProperty(
                transactionSession.assetId
            );
            break;

        case PROPERTY_RELEASE:
            success = releaseMortgage(
                transactionSession.assetId
            );
            break;

        case PROPERTY_BUILD_HOUSE:
            success = buildHouse(
                transactionSession.assetId
            );

            break;

        case PROPERTY_SELL_HOUSE:

            success = sellHouse(
                transactionSession.assetId
            );
            break;

        case PROPERTY_BUILD_HOTEL:
            success = buildHotel(
                transactionSession.assetId
            );
            break;

        case PROPERTY_SELL_HOTEL:
            success = sellHotel(
                transactionSession.assetId
            );
            break;

        case PROPERTY_SELL:
            success = sellProperty(
                transactionSession.assetId,
                transactionSession.sourceRole
            );
            break;
        
        case PROPERTY_TRANSFER:
            success = transferProperty(
                transactionSession.assetId,
                transactionSession.targetRole
            );
            break;

        case PROPERTY_AUCTION_CLAIM:

            // sourceRole = pemenang lelang (yang tap kartu)
            // BUG FIX: sebelumnya pakai transferProperty() yang
            // mensyaratkan properti SUDAH ada owner -> selalu
            // gagal untuk properti hasil lelang (unowned).
            // Sekarang pakai claimAuctionProperty() yang benar.
            success = claimAuctionProperty(
                transactionSession.assetId,
                transactionSession.sourceRole
            );
            break;

        default:
            success = false;
            break;
    }

    return success;
}