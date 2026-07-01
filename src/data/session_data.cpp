#include "session_data.h"

/* =========================
   GLOBAL SESSION
========================= */

ClientSession clients[MAX_CLIENTS];

/* =========================
   GET DEVICE BY CLIENT
========================= */

String getDeviceIdByClientId(uint32_t clientId)
{
    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        if (
            clients[i].connected &&
            clients[i].clientId == clientId
        )
        {
            return clients[i].deviceId;
        }
    }

    return "";
}