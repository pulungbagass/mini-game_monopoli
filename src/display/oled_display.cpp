#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include <qrcode.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

          #define USE_QR false // set to true kalau mau pake QR code display, tapi bakal makan banyak memori, jadi hati-hati

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void initOLED() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED gagal");
    return;
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE); 
}

// ================= IP DISPLAY =================
void showIP(String ip) {
  display.clearDisplay();

  display.setCursor(0, 0);
  display.println("ESP32 IP:");

  display.setCursor(0, 20);
  display.println(ip);

  display.display();
}

// ================= DISPLAY OLET SECUEL ===================

void showSimpleInfo() {
  display.clearDisplay();

  if (WiFi.status() == WL_CONNECTED) {
    String ip = WiFi.localIP().toString();

    display.setCursor(0, 0);
    display.println("Connected!");

    display.setCursor(0, 15);
    display.println("Buka di:");

    display.setCursor(0, 30);
    display.println(ip);
  } else {
    display.setCursor(0, 0);
    display.println("Mode Setup");

    display.setCursor(0, 15);
    display.println("Connect WiFi:");

    display.setCursor(0, 30);
    display.println("ESP32-Setup");

    display.setCursor(0, 45);
    display.println("192.168.4.1");
  }

  display.display();
}

// ================= QR DISPLAY =================
#if USE_QR
void showQR(String url) {
  display.clearDisplay();

  QRCode qrcode;
  uint8_t qrcodeData[qrcode_getBufferSize(3)];

  qrcode_initText(&qrcode, qrcodeData, 3, 0, url.c_str());

  int scale = 2;

  // biar center
  int offsetX = (SCREEN_WIDTH - (qrcode.size * scale)) / 2;
  int offsetY = (SCREEN_HEIGHT - (qrcode.size * scale)) / 2;

  for (uint8_t y = 0; y < qrcode.size; y++) {
    for (uint8_t x = 0; x < qrcode.size; x++) {
      if (qrcode_getModule(&qrcode, x, y)) {
        display.fillRect(
          offsetX + x * scale,
          offsetY + y * scale,
          scale,
          scale,
          WHITE
        );
      }
    }
  }

  display.display();
}
#endif