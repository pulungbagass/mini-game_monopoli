#pragma once

#include <Arduino.h>

/* ======================================================
   GAME LOG (GLOBAL_LOG)
   Ring buffer sederhana yang menyimpan history event
   global (transfer, lelang, properti, dsb) supaya bisa
   ditampilkan di halaman "GAME LOG" (public) maupun
   "TRANSACTION LOG" (bank only) di frontend.
====================================================== */

#define GAME_LOG_MAX 60

enum LogCategory
{
    LOG_INFO,
    LOG_MONEY_IN,     // uang masuk ke role terkait (hijau)
    LOG_MONEY_OUT,    // uang keluar dari role terkait (merah)
    LOG_PROPERTY,     // aksi properti (beli/jual/gadai/bangun)
    LOG_AUCTION,       // lelang
    LOG_CARD           // chance / community chest
};

struct GameLogEntry
{
    unsigned long timestamp;
    LogCategory category;
    String message;

    // role yang paling relevan dengan entry ini
    // (dipakai untuk "History" personal per player)
    String roleA;
    String roleB;
};

/* ======================================================
   API
====================================================== */

void addGameLog(
    LogCategory category,
    const String& message,
    const String& roleA = "",
    const String& roleB = ""
);

int getGameLogCount();

// index 0 = paling lama, count-1 = paling baru
const GameLogEntry& getGameLogAt(int index);

const char* logCategoryToString(LogCategory category);
