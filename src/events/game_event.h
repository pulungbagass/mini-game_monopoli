#pragma once

#include <Arduino.h>

// ======================================================
// Claim Event
// ======================================================

void eventClaimSuccess(
    const String& role,
    const String& deviceId
);

void eventClaimFailed();

// ======================================================
// Transaction Event
// ======================================================

void eventTransactionSuccess();

void eventTransactionFailed();