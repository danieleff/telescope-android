#ifndef STEPPER_H
#define STEPPER_H

#include <Arduino.h>

class Stepper {
  public:
    Stepper(int unused, int stepPin, int dirPin);
    bool isRunning();
    
    void setMaxSpeed(long maxSpeed);
    long maxSpeed();
    
    void setCurrentPosition(long position);
    void moveTo(long position);
    
    void setAcceleration(long ignore);
    
    long currentPosition();
    void run();

    static int DRIVER;
    
  private:
    int stepPin;
    int dirPin;
    long position;
    long moveToPosition;
    long moveToPosition2;
    long maxSpd;
    
    long stepInterval;
    
    unsigned long lastStepTime;
    
};

#endif

