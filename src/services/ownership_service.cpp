#include "ownership_service.h"

#include "../data/ownership_data.h"

// ======================================================
// Claim Role
// ======================================================

bool claimRole(const String& role, const String& deviceId)
{
    if (isRoleOwned(role))
        return false;

    for (int i = 0; i < 7; i++)
    {
        if (ownerships[i].role == "")
        {
            ownerships[i].role = role;
            ownerships[i].deviceId = deviceId;
            return true;
        }
    }

    return false;
}

// ======================================================
// Release Role
// ======================================================

bool releaseRole(const String& role)
{
    for (int i = 0; i < 7; i++)
    {
        if (ownerships[i].role == role)
        {
            ownerships[i].role = "";
            ownerships[i].deviceId = "";
            return true;
        }
    }

    return false;
}

// ======================================================
// Clear Ownership
// ======================================================

void clearOwnership()
{
    for (int i = 0; i < 7; i++)
    {
        ownerships[i].role = "";
        ownerships[i].deviceId = "";
    }
}

// ======================================================
// Validation
// ======================================================

bool isRoleOwned(const String& role)
{
    for (int i = 0; i < 7; i++)
    {
        if (ownerships[i].role == role)
            return true;
    }

    return false;
}

bool isRoleOwner(const String& role, const String& deviceId)
{
    for (int i = 0; i < 7; i++)
    {
        if (ownerships[i].role == role &&
            ownerships[i].deviceId == deviceId)
        {
            return true;
        }
    }

    return false;
}

bool isDeviceRegistered(const String& deviceId)
{
    for (int i = 0; i < 7; i++)
    {
        if (ownerships[i].deviceId == deviceId)
            return true;
    }

    return false;
}

// ======================================================
// Getter
// ======================================================

String getOwner(const String& role)
{
    for (int i = 0; i < 7; i++)
    {
        if (ownerships[i].role == role)
            return ownerships[i].deviceId;
    }

    return "";
}

String getRoleByDevice(const String& deviceId)
{
    for (int i = 0; i < 7; i++)
    {
        if (ownerships[i].deviceId == deviceId)
            return ownerships[i].role;
    }

    return "";
}

// ======================================================
// Debug
// ======================================================

void printOwnership()
{
    Serial.println();
    Serial.println("========== OWNERSHIP ==========");

    for (int i = 0; i < 7; i++)
    {
        if (ownerships[i].role == "")
            continue;

        Serial.print("ROLE   : ");
        Serial.println(ownerships[i].role);

        Serial.print("DEVICE : ");
        Serial.println(ownerships[i].deviceId);

        Serial.println("------------------------------");
    }

    Serial.println("===============================");
    Serial.println();
}