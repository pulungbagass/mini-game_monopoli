#include "ws_auction.h"

#include "../../services/auction_service.h"

extern AsyncWebSocket ws;

/* ======================================================
   HELPER: response singkat ke 1 client
====================================================== */

static void replyError(
    AsyncWebSocketClient *client,
    const String& type,
    const String& reason
)
{
    JsonDocument doc;

    doc["type"] = type;
    doc["reason"] = reason;

    String json;
    serializeJson(doc, json);

    client->text(json);
}

/* ======================================================
   START AUCTION (Bank only)
====================================================== */

void handleStartAuction(
    AsyncWebSocketClient *client,
    JsonDocument &doc
)
{
    String role =
        doc["role"] | String("");

    if (role != "BANK")
    {
        replyError(client, "auction_error", "bank_only");
        return;
    }

    String assetId =
        doc["assetId"].as<String>();

    if (assetId == "")
    {
        replyError(client, "auction_error", "invalid_asset");
        return;
    }

    String errorOut;

    bool started =
        startAuction(assetId, errorOut);

    if (!started)
    {
        replyError(client, "auction_error", errorOut);
    }
}

/* ======================================================
   PLACE BID (Player only)
====================================================== */

void handlePlaceBid(
    AsyncWebSocketClient *client,
    JsonDocument &doc
)
{
    String role =
        doc["role"] | String("");

    int increment =
        doc["increment"] | 0;

    String errorOut;

    bool success =
        placeAuctionBid(role, increment, errorOut);

    if (!success)
    {
        // broadcastAuctionRejected sudah dikirim di dalam
        // placeAuctionBid() untuk kasus insufficient_balance;
        // untuk kasus lain (role/increment invalid) cukup
        // balas ke pengirim saja.
        if (errorOut != "insufficient_balance")
        {
            replyError(client, "auction_error", errorOut);
        }
    }
}

/* ======================================================
   END AUCTION (Bank only, force end)
====================================================== */

void handleEndAuction(
    AsyncWebSocketClient *client,
    JsonDocument &doc
)
{
    String role =
        doc["role"] | String("");

    if (role != "BANK")
    {
        replyError(client, "auction_error", "bank_only");
        return;
    }

    if (!isAuctionActive())
    {
        replyError(client, "auction_error", "not_active");
        return;
    }

    endAuction(true);
}
