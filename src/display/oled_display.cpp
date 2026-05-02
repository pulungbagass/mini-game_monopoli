#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <qrcode.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

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

// ================= QR DISPLAY =================
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