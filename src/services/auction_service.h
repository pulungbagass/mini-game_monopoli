#pragma once

#include <Arduino.h>

/* ======================================================
   AUCTION SERVICE (Phase 2 - New Core Mechanic)
====================================================== */

// Bank memilih properti kosong lalu memulai lelang.
// errorOut diisi kode alasan kalau gagal, contoh:
// "already_running" | "not_buyable" | "already_owned"
bool startAuction(
    const String& assetId,
    String& errorOut
);

// Player menekan salah satu tombol fixed bid (+5/+10/+50/+100).
// errorOut diisi kode alasan kalau ditolak, contoh:
// "not_active" | "invalid_increment" | "insufficient_balance"
bool placeAuctionBid(
    const String& role,
    int increment,
    String& errorOut
);

// forced = true kalau dipicu tombol "Akhiri Lelang" oleh Bank.
// forced = false kalau dipicu timeout 30 detik otomatis.
// Mengembalikan false kalau memang tidak ada lelang aktif.
bool endAuction(bool forced);

bool isAuctionActive();

unsigned long getAuctionRemainingMs();
