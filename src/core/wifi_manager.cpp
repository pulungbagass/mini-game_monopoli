#include <WiFi.h>
#include <Arduino.h>
#include "../config/config.h"
#include "../display/oled_display.h"

void connectWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting to WiFi");

  int retry = 0;

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    retry++;

    if (retry > 20) { // ~10 detik
      Serial.println("\nGagal connect!");
      return;
    }
  }

  Serial.println("\nConnected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  Serial.println(WiFi.localIP());

  String ip = WiFi.localIP().toString();
  String url = "http://" + ip;

  // tampil IP dulu
  showIP(ip);
  delay(3000);

  // baru QR
  showQR(url);
}