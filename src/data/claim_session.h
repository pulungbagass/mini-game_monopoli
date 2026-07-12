#ifndef CLAIM_SESSION_H
#define CLAIM_SESSION_H

#include <Arduino.h>

/* ======================================================
   Claim Session
====================================================== */

struct ClaimSession
{
    bool waiting;

    String role;

    String deviceId;

    unsigned long startTime;
};

extern ClaimSession claimSession;

/* ======================================================
   Helper
====================================================== */

void clearClaimSession();

#endif