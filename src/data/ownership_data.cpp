#include "ownership_data.h"

Ownership ownerships[TOTAL_ROLES];

String pendingRole = "";
String pendingDeviceId = "";
bool waitingForCard = false;