#include "auction_session.h"

AuctionSession auctionSession;

void clearAuctionSession()
{
    auctionSession.active = false;
    auctionSession.assetId = "";
    auctionSession.highestBid = 0;
    auctionSession.highestBidRole = "";
    auctionSession.startTime = 0;
    auctionSession.historyCount = 0;
    auctionSession.awaitingClaim = false;
}

void pushAuctionHistory(
    const String& role,
    int amount,
    int delta
)
{
    if (auctionSession.historyCount >= AUCTION_HISTORY_MAX)
    {
        // geser semua entry ke bawah 1 slot (buang yang
        // paling lama). Riwayat lelang tidak sebanyak
        // game log jadi cukup O(n) shift, aman untuk ESP32.
        for (int i = 1; i < AUCTION_HISTORY_MAX; i++)
        {
            auctionSession.history[i - 1] =
                auctionSession.history[i];
        }

        auctionSession.historyCount = AUCTION_HISTORY_MAX - 1;
    }

    AuctionBidEntry& entry =
        auctionSession.history[auctionSession.historyCount];

    entry.role = role;
    entry.amount = amount;
    entry.delta = delta;

    auctionSession.historyCount++;
}
