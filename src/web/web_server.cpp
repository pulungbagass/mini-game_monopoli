#include "web_server.h"

#include "../data/players_data.h"
#include "../routes/api_routes.h"
#include "../websocket/ws_manager.h"
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
    return;

  }

  Serial.println("SPIFFS READY");


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