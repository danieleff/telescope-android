#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include "Stepper.h"

const long steps_per_turn = 200;
const long gear_ratio = 200;
const long microstep = 1;

//const float STEPPER_RA_TO_ARCMILLIS = 0.0001f;
//const float STEPPER_DEC_TO_ARCMILLIS = 0.0015f;

const float STEPPER_RA_TO_ARCMILLIS = 24.0f / steps_per_turn / gear_ratio / microstep;
const float STEPPER_DEC_TO_ARCMILLIS = 360.0f / steps_per_turn / gear_ratio / microstep;

const byte TRACKING_OFF=0;
const byte TRACKING_FOLLOW=1;
const byte TRACKING_MANUAL=2;

extern byte tracking;


class Motor {
  public:
    void setup(boolean a4988);
    void loop();
    
    float getHourAngle();
    float getDeclination();

    void setHaMaxSpeedPercent(float percent);
    void setDecMaxSpeedPercent(float percent);

    void moveToHourAngle(float ha);
    void moveToDeclination(float dec);

    void clearRa(float ra);
    void clearDec(float dec);

    float getMaxHaPerSecond();
    float getMaxDecPerSecond();

    bool isHaRunning();
    bool isDecRunning();
    
    void run();

  private:
    Stepper *stepperHa;
    Stepper *stepperDec;

    int topHaSpeed;
    int topDecSpeed;
};

extern Motor motor;

#endif

