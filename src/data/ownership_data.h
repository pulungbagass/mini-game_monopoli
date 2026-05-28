#ifndef OWNERSHIP_DATA_H
#define OWNERSHIP_DATA_H

#include <Arduino.h>


struct Ownership {
    String role;
    String deviceId;
};


/* =========================
   ROLE OWNER
========================= */

extern Ownership ownerships[7];


/* =========================
   PENDING CLAIM
========================= */

extern String pendingRole;
extern String pendingDeviceId;
extern bool waitingForCard;
#endif