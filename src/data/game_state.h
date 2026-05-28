#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <Arduino.h>

struct PlayerState {

    String role;
    int money;
    int property;

};


extern PlayerState
playerStates[7];


#endif