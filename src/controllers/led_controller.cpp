#include <Arduino.h>
#include "../config/config.h"

void initLED() {
  pinMode(LED_PIN, OUTPUT);
}

void ledOn() {
  digitalWrite(LED_PIN, HIGH);
}

void ledOff() {
  digitalWrite(LED_PIN, LOW);
}