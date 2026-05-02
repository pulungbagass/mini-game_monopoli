#ifndef OLED_DISPLAY_H
#define OLED_DISPLAY_H

#include <Arduino.h>

void initOLED();
void showIP(String ip);
void showQR(String url);

#endif