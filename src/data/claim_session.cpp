#include "claim_session.h"

/* ======================================================
   Global Session
====================================================== */

ClaimSession claimSession;

/* ======================================================
   Clear Session
====================================================== */

void clearClaimSession()
{
    claimSession.waiting = false;

    claimSession.role = "";

    claimSession.deviceId = "";
}