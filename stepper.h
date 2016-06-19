#ifndef STEPPER_H
#define STEPPER_H

#include <Arduino.h>

class Stepper {
  public:
    Stepper(uint8_t unused, uint8_t stepPin, uint8_t dirPin);
    bool isRunning();
    
    void setMaxSpeed(float maxSpeed);
    float maxSpeed();
    
    void setCurrentPosition(long position);
    void moveTo(long position);
    
    void setAcceleration(float ignore);
    
    long currentPosition();
    void run();

    static int DRIVER;
    
  private:
    uint8_t stepPin;
    uint8_t dirPin;
    long position;
    long moveToPosition;
    long moveToPosition2;
    float maxSpd;
    
    long stepInterval;
    long maxStepInterval;
    
    unsigned long lastStepTime;
};

#endif


