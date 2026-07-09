#ifndef MONOPOLY_REPOSITORY_H
#define MONOPOLY_REPOSITORY_H

#include <Arduino.h>
#include <ArduinoJson.h>

bool loadMonopolyRepository();

JsonDocument& getMonopolyRepository();

#endif