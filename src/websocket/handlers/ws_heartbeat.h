#pragma once

#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>

/* ======================================================
   HEARTBEAT PING-PONG (Fase C - Mobile-Proof Recovery)
   ------------------------------------------------------
   Kenapa app-level JSON, bukan native WS ping/pong frame:
   native ping/pong bisa saja tetap dibalas otomatis oleh
   network stack OS meski tab JS-nya sudah dibekukan (layar
   HP mati / pindah ke app lain), jadi TIDAK benar-benar
   membuktikan JS pemain masih hidup. Ping berbasis pesan
   JSON memaksa ada JS yang jalan untuk membalas -- kalau
   tidak, ESP32 tahu socket itu cuma "mayat" yang menggantung.
====================================================== */

// Interval ESP32 mengirim {"type":"ping"} ke semua client (ms)
#define HEARTBEAT_PING_INTERVAL_MS 5000UL

// Batas waktu tanpa PONG sebelum client dianggap Ghost Socket
// dan ditendang paksa (ms). 3x interval ping supaya toleran ke
// 1 ping yang mungkin ke-drop akibat micro-disconnect biasa,
// bukan langsung kick di percobaan pertama.
#define HEARTBEAT_TIMEOUT_MS 15000UL

// Panggil SEKALI di setiap iterasi loop(). Non-blocking, sudah
// punya rate-limiter internal sendiri (tidak butuh delay()).
void updateHeartbeat();

// Panggil dari ws_manager.cpp saat menerima {"type":"pong"}
void handlePong(AsyncWebSocketClient *client, JsonDocument &doc);
