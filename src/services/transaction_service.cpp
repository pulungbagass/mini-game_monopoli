#include "transaction_service.h"

#include "../data/game_state.h"

/* ======================================================
   Add Money
====================================================== */

bool addMoney(
    const String& role,
    int amount
)
{
    if (amount <= 0)
        return false;

    for (int i = 0; i < 7; i++)
    {
        if (playerStates[i].role == role)
        {
            playerStates[i].money += amount;
            return true;
        }
    }

    return false;
}

/* ======================================================
   Deduct Money
====================================================== */

bool deductMoney(
    const String& role,
    int amount
)
{
    if (amount <= 0)
        return false;

    for (int i = 0; i < 7; i++)
    {
        if (playerStates[i].role == role)
        {
            if (playerStates[i].money < amount)
                return false;

            playerStates[i].money -= amount;
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