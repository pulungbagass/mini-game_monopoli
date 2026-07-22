#include "auction_controller.h"

#include "../services/auction_service.h"

#include "../data/auction_session.h"
#include "../data/transaction_session.h"

#include "../services/transaction_service.h"
#include "../services/transaction_session_service.h"

#include "../websocket/handlers/ws_auction_broadcast.h"
#include "../websocket/handlers/ws_broadcast.h"

#include "../events/game_event.h"
#include "../data/game_log.h"
#include "../services/property_service.h"

/* ======================================================
   UPDATE AUCTION
   Dipanggil tiap loop() utama. Kalau waktu 30 detik habis
   dan lelang masih aktif, otomatis akhiri lelang (bukan
   force-end dari Bank).
====================================================== */

void updateAuction()
{
    if (!isAuctionActive())
        return;

    if (getAuctionRemainingMs() > 0)
        return;

    Serial.println();
    Serial.println("AUCTION TIMEOUT (30s)");

    endAuction(false);
}

/* ======================================================
   UPDATE AUCTION CLAIM (watchdog fase serah-terima)

   BUG FIX: sebelumnya TIDAK ADA timeout sama sekali di fase
   ini. Kalau pemenang lelang tidak pernah tap kartu, mesin
   akan menunggu selamanya (transactionSession tetap active
   tanpa batas waktu), memblokir transaksi lain juga.
====================================================== */

void updateAuctionClaim()
{
    if (!isTransactionActive())
        return;

    if (transactionSession.propertyAction != PROPERTY_AUCTION_CLAIM)
        return;

    unsigned long elapsed =
        millis() - transactionSession.startTime;

    if (elapsed < AUCTION_CLAIM_TIMEOUT_MS)
        return;

    // Simpan info sebelum session di-clear oleh cancelTransaction()
    String winnerRole = transactionSession.sourceRole;
    String assetId = transactionSession.assetId;
    int amount = transactionSession.amount;

    Serial.println();
    Serial.println("========== AUCTION CLAIM TIMEOUT ==========");
    Serial.print("WINNER (tidak tap) : ");
    Serial.println(winnerRole);

    cancelTransaction();

    // Refund: uang sudah dipotong otomatis saat lelang
    // berakhir, tapi karena pemenang tidak pernah tap untuk
    // konfirmasi penerimaan, properti tetap milik Bank dan
    // uangnya WAJIB dikembalikan supaya adil.
    addMoney(winnerRole, amount);

    broadcastGameState();

    broadcastAuctionClaimTimeout(winnerRole, assetId, amount);

    String propertyLabel = assetId;
    JsonObject asset = getAssetById(assetId);
    if (!asset.isNull())
        propertyLabel = asset["asset_name"].as<String>();

    addGameLog(
        LOG_AUCTION,
        winnerRole + " tidak tap kartu dalam 30 detik, lelang " +
            propertyLabel + " dibatalkan & uang direfund",
        winnerRole,
        "BANK"
    );
}
