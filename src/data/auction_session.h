#pragma once

#include <Arduino.h>

/* ======================================================
   AUCTION SESSION (Phase 2 - Hybrid Smart Monopoly)

   Session lelang real-time. Cuma ada 1 lelang aktif dalam
   satu waktu (sesuai spesifikasi: Bank pilih 1 properti
   kosong lalu broadcast ke semua layar player).
====================================================== */

#define AUCTION_DURATION_MS 30000UL
#define AUCTION_HISTORY_MAX 40

struct AuctionBidEntry
{
    String role;
    int amount;
    int delta;
};

struct AuctionSession
{
    bool active;

    String assetId;

    int highestBid;
    String highestBidRole; // "" = belum ada yang bid

    unsigned long startTime;

    AuctionBidEntry history[AUCTION_HISTORY_MAX];
    int historyCount;

    // Menunggu pemenang lelang tap NFC ke device Bank
    // untuk finalisasi kepemilikan (lihat auction_service).
    bool awaitingClaim;
};

extern AuctionSession auctionSession;

void clearAuctionSession();

void pushAuctionHistory(
    const String& role,
    int amount,
    int delta
);
