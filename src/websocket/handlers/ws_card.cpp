#include "ws_card.h"

#include "../../data/card_deck.h"
#include "../../services/card_service.h"
#include "../../events/game_event.h"

extern AsyncWebSocket ws;

/* ======================================================
   DRAW COMMUNITY CHEST
====================================================== */

void handleDrawCommunityChest(
    AsyncWebSocketClient *client,
    JsonDocument &doc
)
{
    String drawerRole =
        doc["role"].as<String>();

    String cardId =
        drawCard(communityChestDeck);

    JsonObject card =
        getCommunityChestCardById(cardId);

    JsonDocument res;

    res["type"] = "community_chest_result";

    res["drawerRole"] = drawerRole;

    res["cardId"] = cardId;

    res["cardText"] = card["card_text"];

    String json;
    serializeJson(res, json);

    ws.textAll(json);

    eventCardDrawn(
        "COMMUNITY CHEST",
        drawerRole,
        card["card_text"].as<String>()
    );

    Serial.println();
    Serial.print("COMMUNITY CHEST DRAWN : ");
    Serial.println(cardId);
}

/* ======================================================
   DRAW CHANCE
====================================================== */

void handleDrawChance(
    AsyncWebSocketClient *client,
    JsonDocument &doc
)
{
    String drawerRole =
        doc["role"].as<String>();

    String cardId =
        drawCard(chanceDeck);

    JsonObject card =
        getChanceCardById(cardId);

    JsonDocument res;

    res["type"] = "chance_result";

    res["drawerRole"] = drawerRole;

    res["cardId"] = cardId;

    res["cardText"] = card["card_text"];

    String json;
    serializeJson(res, json);

    ws.textAll(json);

    eventCardDrawn(
        "CHANCE",
        drawerRole,
        card["card_text"].as<String>()
    );

    Serial.println();
    Serial.print("CHANCE DRAWN : ");
    Serial.println(cardId);
}
