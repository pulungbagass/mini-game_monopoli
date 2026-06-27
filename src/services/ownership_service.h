#pragma once

#include <Arduino.h>

bool isRoleOwned(const String& role);

bool claimRole(
    const String& role,
    const String& deviceId
);

String getOwner(
    const String& role
);