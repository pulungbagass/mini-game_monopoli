#pragma once

#include <Arduino.h>

struct Player {

  String uid;
  String name;

  int money;

  int house;
  int hotel;

};


extern Player players[];

extern const int TOTAL_PLAYERS;