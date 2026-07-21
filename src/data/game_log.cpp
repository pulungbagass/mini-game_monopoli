#include "game_log.h"

#include "../websocket/handlers/ws_log_broadcast.h"

/* ======================================================
   STORAGE
====================================================== */

static GameLogEntry logBuffer[GAME_LOG_MAX];
static int logCount = 0;   // total valid entries (<= GAME_LOG_MAX)
static int logHead  = 0;   // index tempat entry berikutnya ditulis

/* ======================================================
   ADD
====================================================== */

void addGameLog(
    LogCategory category,
    const String& message,
    const String& roleA,
    const String& roleB
)
{
    GameLogEntry& entry = logBuffer[logHead];

    entry.timestamp = millis();
    entry.category = category;
    entry.message = message;
    entry.roleA = roleA;
    entry.roleB = roleB;

    logHead = (logHead + 1) % GAME_LOG_MAX;

    if (logCount < GAME_LOG_MAX)
        logCount++;

    // Broadcast entry baru ke semua client (real-time)
    broadcastGameLogEntry(entry);
}

/* ======================================================
   GET
====================================================== */

int getGameLogCount()
{
    return logCount;
}

const GameLogEntry& getGameLogAt(int index)
{
    // index 0 = paling lama.
    // Karena buffer melingkar (circular), entry paling lama
    // ada di posisi (logHead - logCount + GAME_LOG_MAX) % GAME_LOG_MAX
    // ketika buffer sudah penuh; kalau belum penuh entry
    // paling lama selalu di index 0.

    int start = (logCount < GAME_LOG_MAX)
        ? 0
        : logHead;

    int realIndex = (start + index) % GAME_LOG_MAX;

    return logBuffer[realIndex];
}

const char* logCategoryToString(LogCategory category)
{
    switch (category)
    {
        case LOG_MONEY_IN:  return "money_in";
        case LOG_MONEY_OUT: return "money_out";
        case LOG_PROPERTY:  return "property";
        case LOG_AUCTION:   return "auction";
        case LOG_CARD:      return "card";
        default:            return "info";
    }
}
