#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>

JsonObject getCommunityChestCardById(const String& cardId);

JsonObject getChanceCardById(const String& cardId);
