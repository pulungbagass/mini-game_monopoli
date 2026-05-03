#include <Arduino.h>
#include <WiFi.h>
#include <WiFiManager.h>

#include "server/server.h"
#include "controllers/led_controller.h"
#include "display/oled_display.h"


static unsigned long lastUpdate = 0;


void setup() {
  Serial.begin(115200);
  
  initOLED();
  showIP("Connecting...");
  
  WiFiManager wm;

  wm.setAPCallback([](WiFiManager *wm) {
    Serial.println("AP Mode aktif");

    showSimpleInfo(); // tampil "Mode Setup"
  });

  bool res = wm.autoConnect("ESP32-Setup");

  initLED();
  initServer();
  showSimpleInfo();

  
}

void loop() {
  handleClient();

  if (millis() - lastUpdate > 2000) {
    showSimpleInfo();
    Serial.print("WiFi status: ");
    Serial.println(WiFi.status());
    lastUpdate = millis();
  }
}