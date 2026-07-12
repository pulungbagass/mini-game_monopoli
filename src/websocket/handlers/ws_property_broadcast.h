#pragma once

#include <Arduino.h>

/* ======================================================
   Property Broadcast
====================================================== */

void broadcastProperty(
    const String& assetId
);

void broadcastAllProperties();