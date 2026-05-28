#ifndef NFC_ROLES_H
#define NFC_ROLES_H

#include <Arduino.h>


/* =========================
   UID LIST
========================= */

#define BANK_UID     "F99E6F12"

#define PLAYER1_UID  "89C02412"
#define PLAYER2_UID  "39807F11"
#define PLAYER3_UID  "994F8511"
#define PLAYER4_UID  "19AD8511"
#define PLAYER5_UID  "39828D11"
#define PLAYER6_UID  "29D62A12"


/* =========================
   FUNCTION
========================= */

String getCardRole(String uid);

#endif