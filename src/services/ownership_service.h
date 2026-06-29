#pragma once

#include <Arduino.h>

/* CLAIM */

bool claimRole(const String& role,const String& deviceId);
bool releaseRole(const String& role);
void clearOwnership();

/* VALIDATION */

bool isRoleOwned(const String& role);
bool isRoleOwner(const String& role,const String& deviceId);
bool isDeviceRegistered(const String& deviceId);

/* GETTER */

String getOwner(const String& role);
String getRoleByDevice(const String& deviceId);

/* DEBUG */

void printOwnership();