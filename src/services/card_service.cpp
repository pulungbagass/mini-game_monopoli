#include "card_service.h"

#include "../repositories/monopoly_repository.h"

static JsonObject findCard(
    const char* jsonKey,
    const String& cardId
)
{
    JsonArray cards =
        getMonopolyRepository()[jsonKey];

    for (JsonObject card : cards)
    {
        if (card["card_id"] == cardId)
        {
            return card;
        }
    }

    return JsonObject();
}

JsonObject getCommunityChestCardById(const String& cardId)
{
    return findCard(
        "monopoly_community_chest",
        cardId
    );
}

JsonObject getChanceCardById(const String& cardId)
{
    return findCard(
        "monopoly_chance",
        cardId
    );
}
