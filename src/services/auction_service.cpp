#include "auction_service.h"

#include "../data/auction_session.h"
#include "../data/transaction_session.h"
#include "../data/property_ownership_service.h"

#include "../services/property_service.h"
#include "../services/transaction_service.h"
#include "../services/transaction_session_service.h"

#include "../events/game_event.h"

#include "../websocket/handlers/ws_auction_broadcast.h"

/* ======================================================
   HELPER: validasi increment fixed (+5/+10/+50/+100)
====================================================== */

static bool isValidIncrement(int increment)
{
    return increment == 5 ||
           increment == 10 ||
           increment == 50 ||
           increment == 100;
}

/* ======================================================
   START AUCTION
====================================================== */

bool startAuction(
    const String& assetId,
    String& errorOut
)
{
    if (auctionSession.active)
    {
        errorOut = "already_running";
        return false;
    }

    if (!isBuyable(assetId))
    {
        errorOut = "not_buyable";
        return false;
    }

    if (hasOwner(assetId))
    {
        errorOut = "already_owned";
        return false;
    }

    clearAuctionSession();

    auctionSession.active = true;
    auctionSession.assetId = assetId;
    auctionSession.highestBid = 0;
    auctionSession.highestBidRole = "";
    auctionSession.startTime = millis();
    auctionSession.historyCount = 0;
    auctionSession.awaitingClaim = false;

    broadcastAuctionStarted(
        assetId,
        AUCTION_DURATION_MS
    );

    eventAuctionStarted(assetId);

    Serial.println();
    Serial.println("========== AUCTION STARTED ==========");
    Serial.println(assetId);

    return true;
}

/* ======================================================
   PLACE BID
====================================================== */

bool placeAuctionBid(
    const String& role,
    int increment,
    String& errorOut
)
{
    if (!auctionSession.active)
    {
        errorOut = "not_active";
        return false;
    }

    if (role == "" || role == "BANK")
    {
        errorOut = "invalid_role";
        return false;
    }

    if (!playerExists(role))
    {
        errorOut = "invalid_role";
        return false;
    }

    if (!isValidIncrement(increment))
    {
        errorOut = "invalid_increment";
        return false;
    }

    int newBid =
        auctionSession.highestBid + increment;

    /* =========================================
       SALDO TIDAK CUKUP -> TOLAK, PERTAHANKAN
       HIGHEST BID SEBELUMNYA (spec Phase 2.4)
    ========================================= */

    if (getPlayerMoney(role) < newBid)
    {
        errorOut = "insufficient_balance";

        // kirim ulang state saat ini supaya UI player
        // yang ditolak tetap sinkron dengan highest bid asli
        broadcastAuctionRejected(role, errorOut);

        return false;
    }

    auctionSession.highestBid = newBid;
    auctionSession.highestBidRole = role;

    pushAuctionHistory(role, newBid, increment);

    broadcastAuctionBid(role, newBid, increment);

    eventAuctionBid(role, newBid);

    return true;
}

/* ======================================================
   END AUCTION (force by Bank, or timeout)
====================================================== */

bool endAuction(bool forced)
{
    if (!auctionSession.active)
        return false;

    String assetId = auctionSession.assetId;
    String winnerRole = auctionSession.highestBidRole;
    int winningBid = auctionSession.highestBid;

    auctionSession.active = false;

    /* =========================================
       ADA PEMENANG -> POTONG SALDO OTOMATIS,
       LALU MENUNGGU TAP NFC UNTUK SERAH TERIMA
       KEPEMILIKAN PROPERTI (spec Phase 2.5)
    ========================================= */

    if (winnerRole != "")
    {
        bool deducted =
            deductMoney(winnerRole, winningBid);

        if (!deducted)
        {
            // Saldo berubah di antara bid terakhir dan
            // penutupan lelang (mis. kena transaksi lain).
            // Batalkan kemenangan supaya bank tidak
            // menyerahkan properti tanpa pembayaran.
            Serial.println(
                "[AUCTION] WINNER CANNOT PAY, VOIDING WIN");

            winnerRole = "";
            winningBid = 0;
        }
    }

    if (winnerRole != "")
    {
        bool claimStarted = startTransaction(
            TRANSACTION_PROPERTY,
            PROPERTY_AUCTION_CLAIM,
            winnerRole,
            "BANK",
            assetId,
            winningBid
        );

        if (!claimStarted)
        {
            // Sistem transaksi sedang dipakai proses lain.
            // Uang TETAP sudah terpotong (sesuai spec), tapi
            // serah-terima properti perlu difinalisasi manual
            // oleh Bank lewat Property Manager begitu sistem
            // transaksi kosong kembali.
            Serial.println(
                "[AUCTION] TRANSACTION BUSY, MANUAL CLAIM NEEDED");
        }
    }

    broadcastAuctionEnded(
        assetId,
        winnerRole,
        winningBid
    );

    eventAuctionEnded(assetId, winnerRole, winningBid);

    clearAuctionSession();

    Serial.println();
    Serial.println("========== AUCTION ENDED ==========");
    Serial.print("FORCED : ");
    Serial.println(forced ? "YES" : "NO (timeout)");
    Serial.print("WINNER : ");
    Serial.println(winnerRole == "" ? "NONE" : winnerRole);

    return true;
}

/* ======================================================
   GETTER
====================================================== */

bool isAuctionActive()
{
    return auctionSession.active;
}

unsigned long getAuctionRemainingMs()
{
    if (!auctionSession.active)
        return 0;

    unsigned long elapsed =
        millis() - auctionSession.startTime;

    if (elapsed >= AUCTION_DURATION_MS)
        return 0;

    return AUCTION_DURATION_MS - elapsed;
}
