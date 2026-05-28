#include "ws_claim.h"

#include "../../data/ownership_data.h"


void handleClaim(
    AsyncWebSocketClient *client,
    JsonDocument &doc
) {

    String role =
        doc["role"];

    String deviceId =
        doc["deviceId"];

    pendingRole =
        role;

    pendingDeviceId =
        deviceId;

    waitingForCard =
        true;

    Serial.println(
        "===== CLAIM REQUEST ====="
    );

    Serial.print(
        "ROLE : "
    );

    Serial.println(role);

    Serial.print(
        "DEVICE : "
    );

    Serial.println(deviceId);

    Serial.println(
        "WAITING NFC TAP..."
    );
}