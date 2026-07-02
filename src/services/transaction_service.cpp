#include "transaction_service.h"
#include "../data/players_data.h"

/* ======================================================
   Add Money
====================================================== */

bool addMoney(const String& role, int amount)
{
    if (amount <= 0)
        return false;

    /* =========================
       BANK
    ========================= */

    if (role == "BANK")
        return true;

    /* =========================
       PLAYER
    ========================= */

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

    /* =========================
       BANK
    ========================= */

    if (role == "BANK")
        return true;

    /* =========================
       PLAYER
    ========================= */

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
    if (amount <= 0)
        return false;

    /* =========================
       PLAYER -> BANK
    ========================= */

    if (toRole == "BANK")
    {
        return deductMoney(
            fromRole,
            amount
        );
    }

    /* =========================
       BANK -> PLAYER
    ========================= */

    if (fromRole == "BANK")
    {
        return addMoney(
            toRole,
            amount
        );
    }

    /* =========================
       PLAYER -> PLAYER
    ========================= */

    if (!deductMoney(fromRole, amount))
        return false;

    if (!addMoney(toRole, amount))
    {
        addMoney(fromRole, amount);
        return false;
    }

    return true;
}

/* ======================================================
   Get Player Money
====================================================== */

int getPlayerMoney(const String& role)
{
    if (role == "BANK")
        return 999999;

    for (int i = 0; i < TOTAL_PLAYERS; i++)
    {
        if (players[i].role == role)
        {
            return players[i].money;
        }
    }

    return -1;
}

/* ======================================================
   Player Exists
====================================================== */

bool playerExists(const String& role)
{
    if (role == "BANK")
        return true;

    return getPlayerMoney(role) >= 0;
}