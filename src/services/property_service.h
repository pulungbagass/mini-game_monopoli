#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>

JsonObject getAssetById(const String& assetId);

JsonObject getAssetByName(const String& assetName);

JsonObject getAssetByBoardIndex(int boardIndex);

bool isBuyable(const String& assetId);

int getPurchasePrice(const String& assetId);

int getMortgageValue(const String& assetId);

int getReleaseCost(const String& assetId);

JsonObject getRentData(const String& assetId);

JsonObject getDevelopmentCost(const String& assetId);

int getSellValue(const String& assetId);