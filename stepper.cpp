

#include "stepper.h"

int Stepper::DRIVER = 0;

Stepper::Stepper(int unused, int stepPin, int dirPin) {
  this->stepPin = stepPin;
  this->dirPin = dirPin;
}

void Stepper::setCurrentPosition(long position) {
  this->position = position;
  this->moveToPosition = position;
  this->moveToPosition2 = position;
}

long Stepper::currentPosition() {
  return position;
}

void Stepper::moveTo(long moveToPosition) {
  this->moveToPosition = moveToPosition;
}

bool Stepper::isRunning() {
  return this->position != moveToPosition;
}

void Stepper::setMaxSpeed(long maxSpeed) {
  this->maxSpd = maxSpd;
}

long Stepper::maxSpeed() {
  return this->maxSpd;
}

void Stepper::setAcceleration(long ignore) {
  
}

void Stepper::run() {
  if (position == moveToPosition) return;
  
  unsigned long time = micros();
  unsigned long nextStepTime = lastStepTime;
  
  if (   ((nextStepTime >= lastStepTime) && ((time >= nextStepTime) || (time < lastStepTime)))
       || ((nextStepTime < lastStepTime) && ((time >= nextStepTime) && (time < lastStepTime)))) {
    
    digitalWrite(stepPin, HIGH);
  
    position += (position<moveToPosition) ? 1 : -1;
    
    lastStepTime = time;
    if ( abs(position - moveToPosition) < 100) {
      stepInterval += 10;
    } else if (stepInterval>600) {
      stepInterval -= 8;
    }
    
    digitalWrite(stepPin, LOW);
    
  }
  
}

