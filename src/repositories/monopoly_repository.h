#ifndef MONOPOLY_REPOSITORY_H
#define MONOPOLY_REPOSITORY_H

#include <Arduino.h>
#include <ArduinoJson.h>

bool loadMonopolyRepository();

JsonObject getAssetById(const String& assetId);
JsonObject getAssetByName(const String& assetName);

JsonObject getCornerByName(const String& cornerName);

JsonObject getTaxByName(const String& taxName);

JsonObject getChanceCard(int index);

JsonObject getCommunityChestCard(int index);

int getAssetCount();
int getChanceCount();
int getCommunityChestCount();

#endif