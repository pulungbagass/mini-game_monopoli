#pragma once

#include <Arduino.h>

bool transferMoney(
    const String& fromRole,
    const String& toRole,
    int amount
);

bool addMoney(
    const String& role,
    int amount
);

bool deductMoney(
    const String& role,
    int amount
);