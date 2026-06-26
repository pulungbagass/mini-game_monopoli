#include <Arduino.h>
#include <WiFi.h>
#include <WiFiManager.h>

#include "nfc/nfc_reader.h"
#include "web/web_server.h"
#include "display/oled_display.h"
#include "notification/notification.h"

#include "websocket/handlers/ws_broadcast.h"

WiFiManager wm;

unsigned long lastOLEDUpdate = 0;

void setup() {
  Serial.begin(115200);
  initNFC();

  Serial.println(
    "SETUP JALAN SEKALI"
  );

  initOLED();
  notificationBegin();
  showIP("Connecting...");
  wm.setConfigPortalBlocking(false);
  // wm.setConfigPortalTimeout(180);
  wm.setDebugOutput(false);
  wm.autoConnect("ESP32-Setup");
  initWebServer();
}

void loop() {
  wm.process();
  updateNFC();

  /* =========================
     GAME STATE BROADCAST
  ========================= */

  static unsigned long lastBroadcast = 0;

  if (
      millis() - lastBroadcast > 1000
  ) {
      broadcastGameState();
      lastBroadcast = millis();
  }

  /* =========================
     OLED UPDATE
  ========================= */

  if (
    millis() - lastOLEDUpdate > 2000
  ) {
    showSimpleInfo();
    lastOLEDUpdate = millis();
  }
}