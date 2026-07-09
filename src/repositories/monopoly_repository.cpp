#include "monopoly_repository.h"

#include <SPIFFS.h>

static JsonDocument monopolyDoc;

bool loadMonopolyRepository()
{
    File file = SPIFFS.open("/monopoly_rules.json", "r");

    if(!file)
        return false;

    DeserializationError err =
        deserializeJson(monopolyDoc, file);

    file.close();

    return !err;
}

JsonDocument& getMonopolyRepository()
{
    return monopolyDoc;
}