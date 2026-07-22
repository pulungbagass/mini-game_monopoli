#include "ws_manager.h"

/* =========================
   HANDLERS
========================= */

#include "handlers/ws_register.h"
#include "handlers/ws_claim.h"
#include "handlers/ws_access.h"
#include "handlers/ws_transaction_start.h"
#include "handlers/ws_transaction.h"
#include "handlers/ws_transaction_cancel.h"
#include "handlers/ws_property.h"
#include "handlers/ws_property_broadcast.h"
#include "handlers/ws_property_force.h"
#include "handlers/ws_card.h"
#include "handlers/ws_auction.h"
#include "handlers/ws_auction_broadcast.h"
#include "handlers/ws_log_broadcast.h"
#include "handlers/ws_broadcast.h"

#include "../web/web_server.h"

#include "../data/session_data.h"

#include <ArduinoJson.h>


/* =========================
   WEBSOCKET
========================= */

AsyncWebSocket ws("/ws");


/* =========================
   EVENT
========================= */

void onWebSocketEvent(

    AsyncWebSocket *server,
    AsyncWebSocketClient *client,
    AwsEventType type,

    void *arg,
    uint8_t *data,
    size_t len

) {

    switch (type) {

        /* =========================
           CONNECT
        ========================= */

        case WS_EVT_CONNECT:

            Serial.println(
                "CLIENT CONNECTED"
            );

            Serial.print(
                "CLIENT ID : "
            );

            Serial.println(
                client->id()
            );

            client->text(
                "CONNECTED TO ESP32"
            );

            broadcastAllProperties();

            sendAuctionSnapshot(client);
            sendGameLogSnapshot(client);

            break;


        /* =========================
           DISCONNECT
        ========================= */

        case WS_EVT_DISCONNECT:

            Serial.println(
                "CLIENT DISCONNECTED"
            );

            Serial.print(
                "CLIENT ID : "
            );

            Serial.println(
                client->id()
            );

            // FIX (Phase 1 audit): sebelumnya clients[].connected
            // TIDAK PERNAH di-set false saat disconnect, jadi
            // Player Manager (online/offline monitor) tidak
            // akan pernah akurat.
            for (int i = 0; i < MAX_CLIENTS; i++)
            {
                if (clients[i].clientId == client->id())
                {
                    clients[i].connected = false;
                    break;
                }
            }

            broadcastGameState();

            break;


        /* =========================
           DATA
        ========================= */

        case WS_EVT_DATA: {

            AwsFrameInfo *info =
                (AwsFrameInfo*)arg;

            if (
                info->opcode != WS_TEXT
            ) {
                return;
            }

            String message = "";

            for (
                size_t i = 0;
                i < len;
                i++
            ) {

                message +=
                    (char)data[i];
            }

            Serial.println(
                "MESSAGE RECEIVED:"
            );

            Serial.println(
                message
            );

            JsonDocument doc;

            deserializeJson(
                doc,
                message
            );

            String msgType =
                doc["type"];

            /* =========================
            START TRANSACTION
            ========================= */

            if(
                msgType ==
                "start_transaction"
            )
            {
                handleTransactionStart(
                    client,
                    doc
                );
            }
            else if(
                msgType ==
                "cancel_transaction"
            )
            {
                handleTransactionCancel(
                    client,
                    doc
                );
            }

            /* =========================
            TRANSACTION
            ========================= */

            if (
                msgType ==
                "request_transfer"
            )
            {
                handleTransaction(
                    client,
                    doc
                );
            }

            /* =========================
               REGISTER
            ========================= */

            if (
                msgType == "register"
            ) {

                handleRegister(
                    client,
                    doc
                );
            }


            /* =========================
               CLAIM ROLE
            ========================= */

            if (
                msgType == "claim_role"
            ) {

                handleClaim(
                    client,
                    doc
                );
            }


            /* =========================
               ACCESS
            ========================= */

            if (
                msgType ==
                "request_access"
            ) {

                handleAccess(
                    client,
                    doc
                );
            }


            /* =========================
               PROPERTY
            ========================= */

            if (
                msgType ==
                "buy_property"
            ) {

                handleBuyProperty(
                    client,
                    doc
                );
            }

            if (
                msgType ==
                "sell_property"
            ) {

                handleSellProperty(
                    client,
                    doc
                );
            }

            if (
                msgType ==
                "mortgage_property"
            ) {

                handleMortgageProperty(
                    client,
                    doc
                );
            }

            /* =========================
               BANK EMERGENCY ACTIONS
            ========================= */

            if (
                msgType ==
                "force_mortgage_property"
            ) {

                handleForceMortgage(
                    client,
                    doc
                );
            }

            if (
                msgType ==
                "force_sell_property"
            ) {

                handleForceSell(
                    client,
                    doc
                );
            }

            if (
                msgType ==
                "release_mortgage"
            ) {

                handleReleaseMortgage(
                    client,
                    doc
                );
            }

            if (
                msgType ==
                "build_house"
            ) {

                handleBuildHouse(
                    client,
                    doc
                );
            }

            if (
                msgType ==
                "sell_house"
            ) {

                handleSellHouse(
                    client,
                    doc
                );
            }

            if (
                msgType ==
                "build_hotel"
            ) {

                handleBuildHotel(
                    client,
                    doc
                );
            }

            if (
                msgType ==
                "sell_hotel"
            ) {

                handleSellHotel(
                    client,
                    doc
                );
            }

            /* =========================
               CARDS (CC / CHANCE)
            ========================= */

            if (
                msgType ==
                "draw_community_chest"
            ) {

                handleDrawCommunityChest(
                    client,
                    doc
                );
            }

            if (
                msgType ==
                "draw_chance"
            ) {

                handleDrawChance(
                    client,
                    doc
                );
            }

            /* =========================
               AUCTION (Phase 2)
            ========================= */

            if (
                msgType ==
                "start_auction"
            ) {

                handleStartAuction(
                    client,
                    doc
                );
            }

            if (
                msgType ==
                "place_bid"
            ) {

                handlePlaceBid(
                    client,
                    doc
                );
            }

            if (
                msgType ==
                "end_auction"
            ) {

                handleEndAuction(
                    client,
                    doc
                );
            }

            break;
        }


        /* =========================
           OTHER
        ========================= */

        case WS_EVT_PONG:
        case WS_EVT_ERROR:

            break;
    }
}


/* =========================
   INIT
========================= */

void initWebSocket() {

    ws.onEvent(
        onWebSocketEvent
    );

    server.addHandler(&ws);

    Serial.println(
        "WEBSOCKET READY"
    );
}