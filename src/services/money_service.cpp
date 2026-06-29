#include "money_service.h"
#include "../data/players_data.h"

/* ======================================================
   Add Money
====================================================== */

bool addMoney(const String& role, int amount)
{
    if (amount <= 0)
        return false;

    for (int i = 0; i < TOTAL_PLAYERS; i++)
    {
        if (players[i].role == role)
        {
            players[i].money += amount;
            return true;
        }
    }

    return false;
}

/* ======================================================
   Deduct Money
====================================================== */

bool deductMoney(const String& role, int amount)
{
    if (amount <= 0)
        return false;

    for (int i = 0; i < TOTAL_PLAYERS; i++)
    {
        if (players[i].role == role)
        {
            if (players[i].money < amount)
                return false;

            players[i].money -= amount;
            return true;
        }
    }

    return false;
}

/* ======================================================
   Transfer Money
====================================================== */

bool transferMoney(
    const String& fromRole,
    const String& toRole,
    int amount
)
{
    if (!deductMoney(fromRole, amount))
        return false;

    if (!addMoney(toRole, amount))
    {
        addMoney(fromRole, amount);
        return false;
    }

    return true;
}