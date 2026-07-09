#include "nfc_reader.h"

#include "../data/nfc_roles.h"

#include "../services/ownership_service.h"
#include "../notification/notification.h"
#include "../websocket/handlers/ws_broadcast.h"
#include "../websocket/handlers/ws_claim.h"
#include "../data/claim_session.h"
#include "../data/transaction_session.h"
#include "../transaction/transaction_handler.h"
#include "../websocket/handlers/nfc_transaction_handler.h"

#include <SPI.h>
#include <Adafruit_PN532.h>

/* ======================================================
   PN532 SPI
====================================================== */

#define PN532_SS 14

Adafruit_PN532 nfc(PN532_SS);

/* ======================================================
   INIT NFC
====================================================== */

void initNFC()
{
    nfc.begin();

    uint32_t versiondata = nfc.getFirmwareVersion();

    if (!versiondata)
    {
        Serial.println("PN532 NOT FOUND");
        return;
    }

    Serial.println("PN532 READY");

    nfc.SAMConfig();
}

/* ======================================================
   UPDATE NFC
====================================================== */

void updateNFC()
{
    uint8_t success;
    uint8_t uid[7];
    uint8_t uidLength;

    success = nfc.readPassiveTargetID(
        PN532_MIFARE_ISO14443A,
        uid,
        &uidLength,
        50
    );

    if (!success)
        return;

    /* ======================================================
       Convert UID
    ====================================================== */

    String uidString = "";

    for (uint8_t i = 0; i < uidLength; i++)
    {
        if (uid[i] < 0x10)
            uidString += "0";

        uidString += String(uid[i], HEX);
    }

    uidString.toUpperCase();

    String role = getCardRole(uidString);

    /* ======================================================
       Notification
    ====================================================== */

    notifyCardScan();


    

    /* ======================================================
       Claim Validation
    ====================================================== */

    if (claimSession.waiting)
    {
        Serial.println("VALIDATING CLAIM...");

        if (role == claimSession.role)
        {
            if (isRoleOwned(role))
            {
                Serial.println("ROLE ALREADY OWNED");

                notifyClaimFailed();
            }
            else
            {
                claimRole(
                    role,
                    claimSession.deviceId
                );

                Serial.println("CLAIM SUCCESS");

                sendAccessGranted(
                    role,
                    claimSession.deviceId
                );

                notifyClaimSuccess();

                Serial.print("ROLE  : ");
                Serial.println(role);

                Serial.print("OWNER : ");
                Serial.println(claimSession.deviceId);
            }
        }
        else
        {
            Serial.println("CLAIM FAILED");
            Serial.println("WRONG CARD");

            notifyClaimFailed();
        }

        claimSession.waiting = false;
        claimSession.role = "";
        claimSession.deviceId = "";

        /* ======================================================
           Debug Ownership
        ====================================================== */

        printOwnership();
    }

    /* ======================================================
    TRANSACTION
    ====================================================== */

    handleTransactionCard(role);

    /* ======================================================
       Debug NFC
    ====================================================== */

    Serial.println("===== NFC DETECTED =====");

    Serial.print("ROLE : ");
    Serial.println(role);

    Serial.print("UID  : ");
    Serial.println(uidString);

    Serial.println();

    delay(1000);
}