#include <Arduino.h>
#include <WiFi.h>
#include <WiFiManager.h>

#include "server/server.h"
#include "controllers/led_controller.h"
#include "display/oled_display.h"

WiFiManager wm;

unsigned long lastUpdate = 0;

void setup() {
  Serial.begin(115200);

  Serial.println("SETUP JALAN SEKALI");
  initOLED();
  showIP("Connecting...");

  wm.setConfigPortalBlocking(false);

  // wm.setConfigPortalTimeout(180);

  wm.setDebugOutput(false);
  wm.autoConnect("ESP32-Setup");

  initLED();
  initServer();
}

void loop() {
  wm.process();

  handleClient();

  // update OLED tiap 2 detik
  if (millis() - lastUpdate > 2000) {
    showSimpleInfo();

    Serial.print("WiFi status: ");
    Serial.println(WiFi.status());

    lastUpdate = millis();
  }
}