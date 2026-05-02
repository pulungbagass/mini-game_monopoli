#include <Arduino.h>
#include "core/wifi_manager.h"
#include "server/server.h"
#include "controllers/led_controller.h"
#include "display/oled_display.h"

void setup() {
  Serial.begin(115200);

  initOLED();   
  initLED();
  connectWiFi();
  initServer();
}

void loop() {
  handleClient();
}