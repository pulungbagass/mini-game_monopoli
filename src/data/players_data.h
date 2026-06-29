#pragma once

#include <Arduino.h>

constexpr int TOTAL_PLAYERS = 6;

struct Player
{
    String role;
    String uid;
    String name;

    int money;

    int property;

    int house;
    int hotel;
};

extern Player players[];