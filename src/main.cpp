#include <Arduino.h>
#include <WiFi.h>
#include <WiFiManager.h>

#include "nfc/nfc_reader.h"
#include "web/web_server.h"
#include "display/oled_display.h"
#include "notification/notification.h"
#include "controllers/transaction_controller.h"
#include "controllers/claim_controller.h"
#include "controllers/auction_controller.h"
#include "services/property_service.h"
#include "services/property_transaction_service.h"
#include "services/ownership_service.h"
#include "data/property_ownership_service.h"
#include "data/card_deck.h"

#include "websocket/handlers/ws_broadcast.h"

WiFiManager wm;

unsigned long lastOLEDUpdate = 0;

void setup()
{
    Serial.begin(115200);

    initNFC();

    initOLED();
    notificationBegin();

    showIP("Connecting...");

    wm.setConfigPortalBlocking(false);
    wm.setDebugOutput(false);
    wm.autoConnect("ESP32-Setup");

    initWebServer();
    
    initPropertyOwnership();

    initCardDecks();
    
}

void loop() {
  wm.process();
  updateNFC();

  /* =========================
     GAME STATE BROADCAST
  ========================= */

  static unsigned long lastBroadcast = 0;

  if (
      millis() - lastBroadcast > 1000
  ) {
      broadcastGameState();
      lastBroadcast = millis();
  }

  updateTransaction();

  updateClaimSession();

  updateAuction();

  updateAuctionClaim();

  /* =========================
     OLED UPDATE
  ========================= */

  if (
    millis() - lastOLEDUpdate > 2000
  ) {
    showSimpleInfo();
    lastOLEDUpdate = millis();
  }
}