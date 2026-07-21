#include "ownership_service.h"

#include "../data/ownership_data.h"
#include "../data/session_data.h"

// ======================================================
// Claim Role
// ======================================================

bool claimRole(const String& role, const String& deviceId)
{
    if (isRoleOwned(role))
        return false;

    for(int i=0;i<TOTAL_ROLES;i++)
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
    for(int i=0;i<TOTAL_ROLES;i++)
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
    for(int i=0;i<TOTAL_ROLES;i++)
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
    for(int i=0;i<TOTAL_ROLES;i++)
    {
        if (ownerships[i].role == role)
            return true;
    }

    return false;
}

bool isRoleOwner(const String& role, const String& deviceId)
{
    for(int i=0;i<TOTAL_ROLES;i++)
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
    for(int i=0;i<TOTAL_ROLES;i++)
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
    for(int i=0;i<TOTAL_ROLES;i++)
    {
        if (ownerships[i].role == role)
            return ownerships[i].deviceId;
    }

    return "";
}

String getRoleByDevice(const String& deviceId)
{
    for(int i=0;i<TOTAL_ROLES;i++)
    {
        if (ownerships[i].deviceId == deviceId)
            return ownerships[i].role;
    }

    return "";
}

bool isRoleOnline(const String& role)
{
    String deviceId = getOwner(role);

    if (deviceId == "")
        return false;

    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        if (clients[i].connected &&
            clients[i].deviceId == deviceId)
        {
            return true;
        }
    }

    return false;
}

// ======================================================
// Debug
// ======================================================

void printOwnership()
{
    Serial.println();
    Serial.println("========== OWNERSHIP ==========");

    for(int i=0;i<TOTAL_ROLES;i++)
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