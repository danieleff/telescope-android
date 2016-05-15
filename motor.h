#ifndef MOTOR_H
#define MOTOR_H

#include <AccelStepper.h>

const float STEPPER_RA_TO_ARCMILLIS = 0.0001f;
const float STEPPER_DEC_TO_ARCMILLIS = 0.0015f;

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

    float getMaxHaPerSecond();
    float getMaxDecPerSecond();
    
    void run();

  private:
    AccelStepper *stepperHa;
    AccelStepper *stepperDec;

    int topHaSpeed;
    int topDecSpeed;
};

extern Motor motor;

#endif

