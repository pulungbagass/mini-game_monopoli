#pragma once

#include <Arduino.h>
#include <ESPAsyncWebServer.h>

struct GameLogEntry;

void broadcastGameLogEntry(
    const GameLogEntry& entry
);

// Dipanggil saat client baru connect, supaya halaman
// GAME LOG / TRANSACTION LOG langsung terisi history
// yang sudah ada (bukan cuma event baru).
void sendGameLogSnapshot(
    AsyncWebSocketClient* client
);
