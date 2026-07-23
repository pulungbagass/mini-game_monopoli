#include "ws_sync.h"

#include "../../data/auction_session.h"
#include "../../services/auction_service.h"
#include "ws_auction_broadcast.h"

void handleSyncReq(
    AsyncWebSocketClient *client,
    JsonDocument &doc
) {

    String role = doc["role"] | "";

    JsonDocument res;

    res["type"] = "sync_res";
    res["role"] = role;

    /* ==========================================================
       Saat ini satu-satunya sesi real-time yang bisa "hilang"
       dari layar HP akibat disconnect adalah LELANG (auction),
       karena state-nya di frontend cuma disimpan di memori JS
       (window.appState.auction) yang tidak ikut hilang selama
       halaman tidak reload -- TAPI modal-nya perlu dimunculkan
       ulang secara eksplisit begitu koneksi pulih.

       Kalau nanti ada sesi lain yang butuh recovery serupa
       (mis. transactionSession / claimSession), tambahkan
       cabang else-if di sini dengan pola yang sama.
    ========================================================== */

    if (auctionSession.active) {

        res["current_state"]   = "AUCTION_ACTIVE";
        res["target_property"] = auctionSession.assetId;
        res["highest_bid"]     = auctionSession.highestBid;
        res["highest_bidder"]  = auctionSession.highestBidRole;
        res["remainingMs"]     = getAuctionRemainingMs();

    } else {

        res["current_state"] = "IDLE";
    }

    String response;
    serializeJson(res, response);

    client->text(response);

    // Susulan: snapshot LENGKAP (nama aset, color group, history
    // bid, dll) lewat fungsi yang sudah ada, supaya modal tidak
    // cuma tampil angka mentah tapi identik dengan tampilan normal.
    if (auctionSession.active) {
        sendAuctionSnapshot(client);
    }
}
