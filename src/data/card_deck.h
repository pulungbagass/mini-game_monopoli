#pragma once

#include <Arduino.h>

#define DECK_SIZE 16

/* ======================================================
   Card Deck
   order[] menyimpan urutan card_id hasil shuffle.
   topIndex berputar circular -> efeknya identik dengan
   "ambil 1 kartu dari atas, taruh kembali di paling
   bawah tumpukan" seperti aturan asli Monopoli, tanpa
   perlu reshuffle ulang tiap kali (kartu tidak akan
   berulang sampai seluruh 16 kartu habis diambil).
====================================================== */

struct CardDeck
{
    String order[DECK_SIZE];

    int topIndex;
};

extern CardDeck communityChestDeck;

extern CardDeck chanceDeck;

/* ======================================================
   Init (isi dari monopoly_rules.json lalu shuffle sekali)
====================================================== */

void initCardDecks();

/* ======================================================
   Draw (ambil kartu teratas, otomatis lanjut ke kartu
   berikutnya untuk draw selanjutnya)
====================================================== */

String drawCard(CardDeck& deck);
