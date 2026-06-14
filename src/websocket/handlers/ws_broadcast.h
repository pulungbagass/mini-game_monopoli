#ifndef WS_BROADCAST_H
#define WS_BROADCAST_H

#include <Arduino.h>

void broadcastGameState();

void sendAccessGranted(
    String role,
    String deviceId
);

#endif