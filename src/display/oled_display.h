#ifndef OLED_DISPLAY_H
#define OLED_DISPLAY_H

#include <Arduino.h>

void initOLED();
void showSimpleInfo();
void showIP(String ip);


        #if USE_QR
        void showQR(String url);
        #endif

#endif