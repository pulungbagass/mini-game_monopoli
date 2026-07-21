#include "ws_auction_broadcast.h"

#include "../../data/auction_session.h"
#include "../../services/property_service.h"
#include "../../services/auction_service.h"
#include "../ws_manager.h"

#include <ArduinoJson.h>

extern AsyncWebSocket ws;

/* ======================================================
   HELPER: isi field kartu properti ke JsonObject
====================================================== */

static void fillAssetInfo(JsonObject& target, const String& assetId)
{
    JsonObject asset = getAssetById(assetId);

    target["assetId"] = assetId;

    if (!asset.isNull())
    {
        target["assetName"] = asset["asset_name"];
        target["colorGroup"] = asset["color_group"];
        target["type"] = asset["type"];
        target["purchasePrice"] = asset["purchase_price"];
    }
}

/* ======================================================
   AUCTION STARTED
====================================================== */

void broadcastAuctionStarted(
    const String& assetId,
    unsigned long durationMs
)
{
    JsonDocument doc;

    doc["type"] = "auction_started";

    JsonObject property = doc["property"].to<JsonObject>();
    fillAssetInfo(property, assetId);

    doc["durationMs"] = durationMs;
    doc["highestBid"] = 0;
    doc["highestBidRole"] = "";

    String response;
    serializeJson(doc, response);

    ws.textAll(response);
}

/* ======================================================
   AUCTION BID (broadcast ke semua layar)
====================================================== */

void broadcastAuctionBid(
    const String& role,
    int newHighestBid,
    int delta
)
{
    JsonDocument doc;

    doc["type"] = "auction_bid";

    doc["role"] = role;
    doc["highestBid"] = newHighestBid;
    doc["delta"] = delta;
    doc["remainingMs"] = getAuctionRemainingMs();

    String response;
    serializeJson(doc, response);

    ws.textAll(response);
}

/* ======================================================
   AUCTION BID REJECTED (cuma ke pengirim, bukan broadcast)
   NOTE: karena kita tidak selalu tahu clientId pengirim di
   sini (dipanggil dari service layer), kita broadcast versi
   ringan supaya SEMUA client tetap sinkron dengan highest
   bid yang benar (client yang ditolak akan mengoreksi UI-nya
   sendiri saat menerima ini, tidak ada state yang berubah).
====================================================== */

void broadcastAuctionRejected(
    const String& role,
    const String& reason
)
{
    JsonDocument doc;

    doc["type"] = "auction_bid_rejected";

    doc["role"] = role;
    doc["reason"] = reason;
    doc["highestBid"] = auctionSession.highestBid;
    doc["highestBidRole"] = auctionSession.highestBidRole;

    String response;
    serializeJson(doc, response);

    ws.textAll(response);
}

/* ======================================================
   AUCTION ENDED
====================================================== */

void broadcastAuctionEnded(
    const String& assetId,
    const String& winnerRole,
    int winningBid
)
{
    JsonDocument doc;

    doc["type"] = "auction_ended";

    doc["assetId"] = assetId;
    doc["winnerRole"] = winnerRole;
    doc["winningBid"] = winningBid;
    doc["hasWinner"] = (winnerRole != "");

    String response;
    serializeJson(doc, response);

    ws.textAll(response);
}

/* ======================================================
   SNAPSHOT (client baru connect di tengah lelang)
====================================================== */

void sendAuctionSnapshot(
    AsyncWebSocketClient* client
)
{
    if (!auctionSession.active)
        return;

    JsonDocument doc;

    doc["type"] = "auction_state";

    JsonObject property = doc["property"].to<JsonObject>();
    fillAssetInfo(property, auctionSession.assetId);

    doc["remainingMs"] = getAuctionRemainingMs();
    doc["highestBid"] = auctionSession.highestBid;
    doc["highestBidRole"] = auctionSession.highestBidRole;

    JsonArray history = doc["history"].to<JsonArray>();

    for (int i = 0; i < auctionSession.historyCount; i++)
    {
        JsonObject item = history.add<JsonObject>();

        item["role"] = auctionSession.history[i].role;
        item["amount"] = auctionSession.history[i].amount;
        item["delta"] = auctionSession.history[i].delta;
    }

    String response;
    serializeJson(doc, response);

    client->text(response);
}
