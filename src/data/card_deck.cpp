#include "card_deck.h"

#include "../repositories/monopoly_repository.h"

#include <esp_system.h>

/* ======================================================
   Global Decks
====================================================== */

CardDeck communityChestDeck;

CardDeck chanceDeck;

/* ======================================================
   Shuffle (Fisher-Yates, pakai hardware RNG esp_random()
   supaya beda tiap boot tanpa perlu randomSeed manual)
====================================================== */

static void shuffleDeck(CardDeck& deck)
{
    for (int i = DECK_SIZE - 1; i > 0; i--)
    {
        int j = esp_random() % (i + 1);

        String temp = deck.order[i];

        deck.order[i] = deck.order[j];

        deck.order[j] = temp;
    }

    deck.topIndex = 0;
}

/* ======================================================
   Fill Deck (ambil semua card_id dari monopoly_rules.json)
====================================================== */

static void fillDeck(CardDeck& deck, const char* jsonKey)
{
    JsonArray cards =
        getMonopolyRepository()[jsonKey];

    int i = 0;

    for (JsonObject card : cards)
    {
        if (i >= DECK_SIZE)
            break;

        deck.order[i] =
            card["card_id"].as<String>();

        i++;
    }

    shuffleDeck(deck);
}

/* ======================================================
   Init
====================================================== */

void initCardDecks()
{
    fillDeck(
        communityChestDeck,
        "monopoly_community_chest"
    );

    fillDeck(
        chanceDeck,
        "monopoly_chance"
    );

    Serial.println("CARD DECKS SHUFFLED & READY");
}

/* ======================================================
   Draw
   Ambil kartu di topIndex, lalu putar topIndex ke posisi
   berikutnya secara circular. Ini setara dengan menaruh
   kartu yang baru diambil ke paling bawah tumpukan --
   kartu yang sama baru akan muncul lagi setelah 16 kartu
   lain (semua kartu di deck) sudah diambil semua.
====================================================== */

String drawCard(CardDeck& deck)
{
    String cardId =
        deck.order[deck.topIndex];

    deck.topIndex =
        (deck.topIndex + 1) % DECK_SIZE;

    return cardId;
}
