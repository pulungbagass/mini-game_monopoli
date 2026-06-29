#pragma once

#include <Arduino.h>
#include "players_data.h"

/* ======================================================
   TOTAL ROLE
====================================================== */

constexpr int TOTAL_ROLES = TOTAL_PLAYERS + 1;

/* ======================================================
   OWNERSHIP
====================================================== */

struct Ownership
{
    String role;
    String deviceId;
};

extern Ownership ownerships[TOTAL_ROLES];

/* ======================================================
   CLAIM SESSION
====================================================== */

extern String pendingRole;
extern String pendingDeviceId;
extern bool waitingForCard;