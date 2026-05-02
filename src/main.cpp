#include <Arduino.h>
#include <WiFi.h>
#include <WiFiManager.h>

#include "server/server.h"
#include "controllers/led_controller.h"
#include "display/oled_display.h"

void setup() {
  Serial.begin(115200);

  WiFiManager wm;

  // wm.resetSettings(); // pakai kalau mau reset WiFi

  bool res = wm.autoConnect("ESP32-Setup");

  if (!res) {
    Serial.println("Gagal connect WiFi");
  } else {
    Serial.println("WiFi Connected!");
    Serial.println(WiFi.localIP());
  }

  initOLED();
  initLED();
  initServer();

  // tampil ke OLED
  showSimpleInfo();
}

void loop() {
  handleClient();
}