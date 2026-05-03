#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
// #include <qrcode.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

          #define USE_QR false // set to true kalau mau pake QR code display, tapi bakal makan banyak memori, jadi hati-hati

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void initOLED() {

  Wire.begin(21, 22);

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
  display.fillScreen(BLACK);

  display.setTextColor(WHITE);

  if (WiFi.status() != WL_CONNECTED) {

    // ===== HEADER =====
    display.setTextSize(1);
    display.setCursor(20, 0);
    display.print("SETUP MODE");

    // garis pembatas
    display.drawLine(0, 10, 128, 10, WHITE);

    // ===== CONTENT =====
    display.setCursor(0, 20);
    display.print("WiFi  :");

    display.setCursor(50, 20);
    display.print("ESP32-Setup");

    display.setCursor(0, 35);
    display.print("IP    :");

    display.setCursor(50, 35);
    display.print("192.168.4.1");

    // ===== FOOTER =====
    display.setCursor(10, 54);
    display.print("Open in browser");

  } else {

    String ip = WiFi.localIP().toString();

    // ===== HEADER =====
    display.setTextSize(1);
    display.setCursor(25, 0);
    display.print("CONNECTED");

    display.drawLine(0, 10, 128, 10, WHITE);

    // ===== CONTENT =====
    display.setCursor(0, 20);
    display.print("Device Online");

    display.setCursor(0, 35);
    display.print("IP :");

    display.setCursor(30, 35);
    display.print(ip);

    // ===== FOOTER =====
    display.setCursor(5, 54);
    display.print("Access via browser");
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

