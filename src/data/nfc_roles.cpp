#include "nfc_roles.h"


String getCardRole(String uid) {
    if (uid == BANK_UID) {
        return "BANK";
    }
    if (uid == PLAYER1_UID) {
        return "PLAYER1";
    }
    if (uid == PLAYER2_UID) {
        return "PLAYER2";
    }
    if (uid == PLAYER3_UID) {
        return "PLAYER3";
    }
    if (uid == PLAYER4_UID) {
        return "PLAYER4";
    }
    if (uid == PLAYER5_UID) {
        return "PLAYER5";
    }
    if (uid == PLAYER6_UID) {
        return "PLAYER6";
    }
    return "UNKNOWN";
}