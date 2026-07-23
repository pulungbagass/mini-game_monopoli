#ifndef SESSION_DATA_H
#define SESSION_DATA_H

#include <Arduino.h>


#define MAX_CLIENTS 10


struct ClientSession {

    String deviceId;

    uint32_t clientId;

    bool connected;

    // Timestamp (millis()) terakhir kali client ini membalas
    // heartbeat PONG. Dipakai untuk mendeteksi "Ghost Socket"
    // (HP layar mati / app dibekukan OS, koneksi menggantung
    // tanpa sinyal close yang jelas).
    unsigned long lastPongMillis;

};


/* =========================
   GLOBAL SESSION
========================= */

extern ClientSession clients[MAX_CLIENTS];

/* =========================
   HELPER
========================= */

String getDeviceIdByClientId(uint32_t clientId);

#endif