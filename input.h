#ifndef INPUT_H
#define INPUT_H

#include <Arduino.h>

const byte T_KEY_UP = 1;
const byte T_KEY_DOWN = 2;
const byte T_KEY_LEFT = 3;
const byte T_KEY_RIGHT = 4;
const byte T_KEY_BACK = 5;
const byte T_KEY_OK = 6;
const byte T_KEY_STOP = 7;
const byte T_KEY_FOLLOW = 8;

const byte T_KEY_STARS = 9;
const byte T_KEY_DSOS = 10;
const byte T_KEY_PLANETS = 11;

class Input {
  public:
    void down(byte key);
    void hold(byte key);
    
};

#endif

