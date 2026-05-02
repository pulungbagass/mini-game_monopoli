#include <WebServer.h>
#include "led_routes.h"
#include "../services/led_service.h"

extern WebServer server;

void handleLEDRoute() {
  String state = server.arg("state");

  String result = handleLED(state);

  if (result == "Invalid") {
    server.send(400, "text/plain", result);
  } else {
    server.send(200, "text/plain", result);
  }
}

void registerLEDRoutes() {
  server.on("/led", handleLEDRoute);
}