#include "game_event.h"

#include "../notification/notification.h"

// websocket
#include "../websocket/handlers/ws_broadcast.h"

// logger
// nanti

// oled
// nanti

// ======================================================

void eventClaimSuccess(
    const String& role,
    const String& deviceId
)
{
    sendAccessGranted(
        role,
        deviceId
    );

    // TODO:
    // Logger
    // OLED
    // Analytics
    notifyClaimSuccess();

    Serial.println(
        "[EVENT] CLAIM SUCCESS"
    );
}

// ======================================================

void eventClaimFailed()
{
    notifyClaimFailed();

    // TODO:
    // Logger
    // OLED
    // Analytics

    Serial.println(
        "[EVENT] CLAIM FAILED"
    );
}

// ======================================================

void eventTransactionSuccess()
{
    notifyTransactionSuccess();

    broadcastGameState();

    // TODO:
    // Logger
    // OLED
    // Analytics
    Serial.println(
        "[EVENT] TRANSACTION SUCCESS"
    );
}

// ======================================================

void eventTransactionFailed()
{
    notifyTransactionFailed();

    // TODO:
    // Logger
    // OLED
    // Analytics
    Serial.println(
        "[EVENT] TRANSACTION FAILED"
    );
}