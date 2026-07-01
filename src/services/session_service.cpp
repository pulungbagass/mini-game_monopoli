#include "session_service.h"
#include "../data/session_data.h"

String getDeviceId(uint32_t clientId)
{
    for(int i=0;i<MAX_CLIENTS;i++)
    {
        if(
            clients[i].clientId == clientId &&
            clients[i].connected
        )
        {
            return clients[i].deviceId;
        }
    }

    return "";
}