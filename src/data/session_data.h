#ifndef SESSION_DATA_H
#define SESSION_DATA_H

#include <Arduino.h>


#define MAX_CLIENTS 10


struct ClientSession {

    String deviceId;

    uint32_t clientId;

    bool connected;

};


/* =========================
   GLOBAL SESSION
========================= */

extern ClientSession clients[MAX_CLIENTS];

#endif