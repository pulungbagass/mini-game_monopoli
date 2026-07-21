#include "auction_controller.h"

#include "../services/auction_service.h"

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
