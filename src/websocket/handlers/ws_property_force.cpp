#include "ws_property_force.h"

#include "../../data/property_ownership_service.h"
#include "../../services/property_transaction_service.h"
#include "../../services/transaction_session_service.h"
#include "../../services/property_service.h"
#include "../../data/game_log.h"

extern AsyncWebSocket ws;

/* ======================================================
   HELPER: balas ke 1 client
====================================================== */

static void replyForce(
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

static String forceAssetName(const String& assetId)
{
    JsonObject asset = getAssetById(assetId);
    if (asset.isNull())
        return assetId;
    return asset["asset_name"].as<String>();
}

/* ======================================================
   FORCE MORTGAGE (Bank only, tanpa tap NFC owner)
====================================================== */

void handleForceMortgage(
    AsyncWebSocketClient *client,
    JsonDocument &doc
)
{
    String role = doc["role"] | String("");

    if (role != "BANK")
    {
        replyForce(client, "property_error", "bank_only");
        return;
    }

    String assetId = doc["assetId"].as<String>();

    if (assetId == "")
    {
        replyForce(client, "property_error", "invalid_asset");
        return;
    }

    // Jangan bentrok dengan transaksi lain yang sedang
    // menunggu tap kartu di properti/asset manapun.
    if (isTransactionActive())
    {
        replyForce(client, "property_error", "transaction_busy");
        return;
    }

    PropertyOwnership* ownership = getOwnership(assetId);

    if (ownership == nullptr || !ownership->owned)
    {
        replyForce(client, "property_error", "not_owned");
        return;
    }

    String ownerRole = ownership->ownerRole;

    bool success = mortgageProperty(assetId);

    if (!success)
    {
        replyForce(client, "property_error", "force_mortgage_failed");
        return;
    }

    // Log khusus supaya jelas ini eksekusi PAKSA oleh Bank,
    // bukan owner yang tap kartu sendiri.
    addGameLog(
        LOG_PROPERTY,
        "BANK memaksa gadai " + forceAssetName(assetId) +
            " milik " + ownerRole + " (force mortgage)",
        ownerRole,
        "BANK"
    );
}

/* ======================================================
   FORCE SELL (Bank only, tanpa tap NFC owner)
====================================================== */

void handleForceSell(
    AsyncWebSocketClient *client,
    JsonDocument &doc
)
{
    String role = doc["role"] | String("");

    if (role != "BANK")
    {
        replyForce(client, "property_error", "bank_only");
        return;
    }

    String assetId = doc["assetId"].as<String>();

    if (assetId == "")
    {
        replyForce(client, "property_error", "invalid_asset");
        return;
    }

    if (isTransactionActive())
    {
        replyForce(client, "property_error", "transaction_busy");
        return;
    }

    PropertyOwnership* ownership = getOwnership(assetId);

    if (ownership == nullptr || !ownership->owned)
    {
        replyForce(client, "property_error", "not_owned");
        return;
    }

    String ownerRole = ownership->ownerRole;

    bool success = sellProperty(assetId, ownerRole);

    if (!success)
    {
        replyForce(client, "property_error", "force_sell_failed");
        return;
    }

    addGameLog(
        LOG_PROPERTY,
        "BANK memaksa jual " + forceAssetName(assetId) +
            " milik " + ownerRole + " (force sell)",
        ownerRole,
        "BANK"
    );
}
