#include "claim_controller.h"

#include "../data/claim_session.h"
#include "../websocket/handlers/ws_claim.h"

/* ======================================================
   UPDATE CLAIM SESSION
====================================================== */

void updateClaimSession()
{
    if (!claimSession.waiting)
        return;

    unsigned long now = millis();

    if (now - claimSession.startTime >= 25000)
    {
        Serial.println();
        Serial.println("CLAIM TIMEOUT");

        sendClaimTimeout();

        clearClaimSession();
    }
}