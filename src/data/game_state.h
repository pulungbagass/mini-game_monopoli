#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <Arduino.h>

struct BankState
{
    int money;
};

extern BankState bankState;

#endif