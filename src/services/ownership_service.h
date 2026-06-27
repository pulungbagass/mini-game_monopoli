#pragma once

#include <Arduino.h>

// Claim & Release
bool claimRole(const String& role, const String& deviceId);
bool releaseRole(const String& role);
void clearOwnership();

// Validation
bool isRoleOwned(const String& role);
bool isRoleOwner(const String& role, const String& deviceId);
bool isDeviceRegistered(const String& deviceId);

// Getter
String getOwner(const String& role);
String getRoleByDevice(const String& deviceId);

// Debug
void printOwnership();