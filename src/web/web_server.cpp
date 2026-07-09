#include "web_server.h"

#include "../data/players_data.h"
#include "../routes/api_routes.h"
#include "../websocket/ws_manager.h"
#include "../repositories/monopoly_repository.h"
#include "../data/property_ownership_service.h"
#include "../services/property_service.h"
#include "../services/property_transaction_service.h"

#include <ArduinoJson.h>

#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>

AsyncWebServer server(80);


/* =========================
   INIT WEB SERVER
========================= */

void initWebServer() {

  if (!SPIFFS.begin(true)) {
    Serial.println("SPIFFS ERROR");
    while (true)
    {
      delay(100);
    }
    return;
  }

  Serial.println("SPIFFS READY");

  // =========================
  // LOAD MONOPOLY REPOSITORY
  // =========================


  if(!loadMonopolyRepository())
  {
      Serial.println("Failed to load monopoly_rules.json");
  }
  else
  {
      Serial.println("Monopoly Repository Loaded");
  }

  
    

  /* =========================
     STATIC FILE
  ========================= */

  server.serveStatic("/", SPIFFS, "/")
        .setDefaultFile("index.html");

  

    

  /* =========================
     404
  ========================= */

  server.onNotFound(

    [](AsyncWebServerRequest *request) {

      Serial.println("404 NOT FOUND");

      Serial.println(
        request->url()
      );

      request->send(
        404,
        "text/plain",
        "NOT FOUND"
      );

    }

  );

  /* =========================
  START SERVER
  ========================= */
  
  setupApiRoutes();
  initWebSocket();
  server.begin();

  Serial.println("WEB SERVER STARTED");

}