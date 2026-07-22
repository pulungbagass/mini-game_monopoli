#pragma once

#include <Arduino.h>
#include <ESPAsyncWebServer.h>

void broadcastAuctionStarted(
    const String& assetId,
    unsigned long durationMs
);

void broadcastAuctionBid(
    const String& role,
    int newHighestBid,
    int delta
);

void broadcastAuctionRejected(
    const String& role,
    const String& reason
);

void broadcastAuctionEnded(
    const String& assetId,
    const String& winnerRole,
    int winningBid
);

/* ======================================================
   AUCTION CLAIM (fase serah-terima properti via tap NFC)
====================================================== */

// Dikirim sekali, tepat setelah lelang berakhir DAN ada
// pemenang. Frontend WAJIB menampilkan banner instruksi
// tap yang jelas & persisten (bukan toast yang hilang
// sendiri) sampai claim_result / claim_timeout diterima.
void broadcastAuctionClaimPending(
    const String& winnerRole,
    const String& assetId,
    int amount,
    unsigned long durationMs
);

// Dikirim saat transaksi klaim (tap NFC pemenang) selesai
// diproses, baik sukses maupun gagal.
void broadcastAuctionClaimResult(
    bool success,
    const String& winnerRole,
    const String& assetId,
    int amount
);

// Dikirim oleh watchdog 30 detik kalau pemenang tidak
// tap kartu sama sekali. refunded selalu true karena uang
// yang sudah dipotong otomatis dikembalikan.
void broadcastAuctionClaimTimeout(
    const String& winnerRole,
    const String& assetId,
    int amount
);

// Dikirim ke 1 client yang baru connect di tengah lelang
// aktif, supaya modal langsung muncul & sinkron.
void sendAuctionSnapshot(
    AsyncWebSocketClient* client
);
