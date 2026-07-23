#pragma once

#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

/* ======================================================
   STATE RECOVERY / SILENT RECONNECT (Fase 3)

   Dipanggil saat frontend mengirim {"type":"sync_req","role":"..."}
   -- biasanya persis setelah WebSocket berhasil connect ulang
   pasca micro-disconnect (sinyal lemah 1-2 detik).

   CATATAN: WS_EVT_CONNECT di ws_manager.cpp SUDAH otomatis
   memanggil sendAuctionSnapshot()+broadcastAllProperties()+
   sendGameLogSnapshot() setiap ada koneksi baru. sync_req ini
   TIDAK menggantikan itu, melainkan jaring pengaman tambahan:
   ringkasan status singkat (current_state) yang bisa dipakai
   frontend untuk SEGERA memunculkan modal yang benar, tanpa
   menunggu event snapshot detail lain selesai diproses.
====================================================== */

void handleSyncReq(
    AsyncWebSocketClient *client,
    JsonDocument &doc
);
