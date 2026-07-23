#include "ws_heartbeat.h"

#include "../ws_manager.h"
#include "../../data/session_data.h"

static unsigned long lastHeartbeatTick = 0;


/* ==========================================================
   TERIMA PONG
========================================================== */

void handlePong(
    AsyncWebSocketClient *client,
    JsonDocument &doc
) {

    uint32_t clientId = client->id();

    for (int i = 0; i < MAX_CLIENTS; i++) {

        if (clients[i].clientId == clientId) {

            clients[i].lastPongMillis = millis();
            break;
        }
    }
}


/* ==========================================================
   KIRIM PING KE SEMUA CLIENT
========================================================== */

static void sendHeartbeatPing() {

    JsonDocument doc;
    doc["type"] = "ping";

    String out;
    serializeJson(doc, out);

    ws.textAll(out);
}


/* ==========================================================
   BERSIHKAN GHOST CLIENT
   ----------------------------------------------------------
   Client yang connected=true tapi tidak PONG dalam
   HEARTBEAT_TIMEOUT_MS dianggap "Ghost Socket" (HP layar mati,
   koneksi menggantung tanpa sinyal close yang jelas). Kita
   paksa tutup di level TCP supaya AsyncWebSocket melepas
   memorinya, dan tandai slot sebagai disconnected supaya
   Player Manager (online/offline monitor) tetap akurat.
========================================================== */

static void cleanupGhostClients() {

    unsigned long now = millis();

    for (int i = 0; i < MAX_CLIENTS; i++) {

        if (!clients[i].connected) continue;
        if (clients[i].deviceId == "") continue;

        if (now - clients[i].lastPongMillis > HEARTBEAT_TIMEOUT_MS) {

            Serial.print("GHOST CLIENT TIMEOUT, KICK: ");
            Serial.println(clients[i].deviceId);

            AsyncWebSocketClient *ghost =
                ws.client(clients[i].clientId);

            if (ghost != nullptr) {
                // Memicu WS_EVT_DISCONNECT normal juga (yang akan
                // ikut broadcastGameState()) -- ini cuma jaga-jaga
                // kalau event itu telat/tidak sempat terpanggil
                // untuk socket yang sudah mati total di sisi client.
                ghost->close();
            }

            clients[i].connected = false;
        }
    }
}


/* ==========================================================
   ENTRY POINT (dipanggil dari loop())
========================================================== */

void updateHeartbeat() {

    unsigned long now = millis();

    if (now - lastHeartbeatTick >= HEARTBEAT_PING_INTERVAL_MS) {

        sendHeartbeatPing();
        cleanupGhostClients();

        lastHeartbeatTick = now;
    }
}
