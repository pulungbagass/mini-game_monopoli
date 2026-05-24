#include <Arduino.h>
#include <WiFi.h>
#include <WiFiManager.h>

#include "web/web_server.h"
#include "display/oled_display.h"

WiFiManager wm;

unsigned long lastOLEDUpdate = 0;

void setup() {
  Serial.begin(115200);

  Serial.println("SETUP JALAN SEKALI");
  initOLED();
  showIP("Connecting...");

  wm.setConfigPortalBlocking(false);

  // wm.setConfigPortalTimeout(180);

  wm.setDebugOutput(false);
  wm.autoConnect("ESP32-Setup");

  initWebServer();
}

void loop() {
  wm.process();

  if (
    millis() - lastOLEDUpdate > 2000
  ) {

    showSimpleInfo();

    lastOLEDUpdate = millis();

  }
}