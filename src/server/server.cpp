#include <WebServer.h>
#include "SPIFFS.h"
#include "../routes/led_routes.h"

WebServer server(80);

void handleFile(String path, String type) {
  File file = SPIFFS.open(path, "r");
  if (!file) {
    server.send(404, "text/plain", "Not Found");
    return;
  }
  server.streamFile(file, type);
  file.close();
}

void setupRoutes() {

  server.onNotFound([]() {
    String uri = server.uri();

    // skip yang gak penting
    if (uri == "/favicon.ico") return;

    Serial.println("=== 404 REQUEST ===");
    Serial.print("URI: ");
    Serial.println(uri);

    Serial.print("Method: ");
    Serial.println(server.method() == HTTP_GET ? "GET" : "POST");

    Serial.print("Args: ");
    Serial.println(server.args());

    for (int i = 0; i < server.args(); i++) {
      Serial.print(" - ");
      Serial.print(server.argName(i));
      Serial.print(": ");
      Serial.println(server.arg(i));
    }

    Serial.println("===================");

    server.send(404, "text/plain", "Not Found");
  });

  server.on("/favicon.ico", []() {
    server.send(204); 
  });
  server.on("/", []() {
    handleFile("/index.html", "text/html");
  });

  server.on("/style.css", []() {
    handleFile("/style.css", "text/css");
  });

  server.on("/script.js", []() {
    handleFile("/script.js", "application/javascript");
  });

  // register modular routes
  registerLEDRoutes();
}

void initServer() {
  if (!SPIFFS.begin(true)) {
    Serial.println("SPIFFS Error");
  }

  server.on("/", []() {
    handleFile("/index.html", "text/html");
  });

  server.on("/style.css", []() {
    handleFile("/style.css", "text/css");
  });

  server.on("/script.js", []() {
    handleFile("/script.js", "application/javascript");
  });

  // optional: favicon biar gak spam
  server.on("/favicon.ico", []() {
    server.send(204);
  });




  setupRoutes();   


  server.begin();
}

void handleClient() {
  server.handleClient();
}