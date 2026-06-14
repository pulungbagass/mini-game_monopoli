#include "nfc_reader.h"
#include "../data/nfc_roles.h"
#include "../data/ownership_data.h"
#include "../websocket/handlers/ws_broadcast.h"

#include <SPI.h>
#include <Adafruit_PN532.h>


/* =========================
   PN532 SPI
========================= */

#define PN532_SS 14


Adafruit_PN532 nfc(PN532_SS);


/* =========================
   INIT NFC
========================= */

void initNFC() {
    nfc.begin();
    uint32_t versiondata =
        nfc.getFirmwareVersion();
    if (!versiondata) {
        Serial.println(
            "PN532 NOT FOUND"
        );
        return;
    }
    Serial.println(
        "PN532 READY"
    );

    nfc.SAMConfig();
}


/* =========================
   UPDATE NFC
========================= */

void updateNFC() {
    uint8_t success;
    uint8_t uid[7];
    uint8_t uidLength;

    success = nfc.readPassiveTargetID(
        PN532_MIFARE_ISO14443A,
        uid,
        &uidLength,
        50
    );

    if (success) {
        String uidString = "";
        for (uint8_t i = 0; i < uidLength; i++) {
            if (uid[i] < 0x10) {
                uidString += "0";
            }
            uidString += String(
                uid[i],
                HEX
            );
        }
        uidString.toUpperCase();
        String role =
            getCardRole(uidString);

        /* =========================
            CLAIM VALIDATION
            ========================= */

            if (waitingForCard) {

                Serial.println(
                    "VALIDATING CLAIM..."
                );


                if (role == pendingRole) {
                    bool alreadyOwned = false;
                    for (int i = 0; i < 7; i++) {
                        if (
                            ownerships[i].role ==
                            role
                        ) {
                            alreadyOwned = true;
                            Serial.println(
                                "ROLE ALREADY OWNED"
                            );
                            break;
                        }
                    }


                    if (!alreadyOwned) {
                        for (int i = 0; i < 7; i++) {
                            if (
                                ownerships[i].role == ""
                            ) {
                                ownerships[i].role =
                                    role;
                                ownerships[i].deviceId =
                                    pendingDeviceId;
                                break;
                            }
                        }

                        Serial.println(
                            "CLAIM SUCCESS"
                            
                        );

                        sendAccessGranted(
                            role,
                            pendingDeviceId
                        );

                        Serial.print(
                            "ROLE : "
                        );

                        Serial.println(role);

                        Serial.print(
                            "OWNER : "
                        );

                        Serial.println(
                            pendingDeviceId
                        );
                    }

                } else {

                    Serial.println(
                        "CLAIM FAILED"
                    );
                    Serial.println(
                        "WRONG CARD"
                    );
                }


                waitingForCard = false;
                pendingRole = "";
                pendingDeviceId = "";


                /* =========================
                DEBUG OWNERSHIP
                ========================= */

                Serial.println(
                    "===== OWNERSHIP LIST ====="
                );
                for (int i = 0; i < 7; i++) {
                    if (
                        ownerships[i].role != ""
                    ) {

                        Serial.print(
                            "ROLE : "
                        );

                        Serial.println(
                            ownerships[i].role
                        );

                        Serial.print(
                            "OWNER : "
                        );

                        Serial.println(
                            ownerships[i].deviceId
                        );

                        Serial.println();
                    }
                }
            }
        Serial.println(
            "===== NFC DETECTED ====="
        );
        Serial.print(
            "ROLE : "
        );
        Serial.println(role);
        Serial.print(
            "UID : "
        );
        Serial.println(uidString);
        Serial.println();
        delay(1000);
    }
}