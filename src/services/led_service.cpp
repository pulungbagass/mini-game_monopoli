#include "led_service.h"
#include "../controllers/led_controller.h"

String handleLED(String state) {
  if (state == "on") {
    ledOn();
    return "LED ON";
  } 
  else if (state == "off") {
    ledOff();
    return "LED OFF";
  }
  return "Invalid";
}