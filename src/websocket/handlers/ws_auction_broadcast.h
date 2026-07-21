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

// Dikirim ke 1 client yang baru connect di tengah lelang
// aktif, supaya modal langsung muncul & sinkron.
void sendAuctionSnapshot(
    AsyncWebSocketClient* client
);
