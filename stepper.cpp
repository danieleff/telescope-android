#include "stepper.h"

#define START_INTERVAL 1400

int Stepper::DRIVER = 0;

Stepper::Stepper(uint8_t unused, uint8_t stepPin, uint8_t dirPin) {
  
  this->stepPin = stepPin;
  this->dirPin = dirPin;
  setCurrentPosition(0);

  this->stepInterval = START_INTERVAL;

  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  digitalWrite(dirPin, HIGH);
}

void Stepper::setCurrentPosition(long pos) {
  this->position = pos;
  this->moveToPosition = this->position;
  this->moveToPosition2 =this-> position;
}

long Stepper::currentPosition() {
  return this->position;
}

void Stepper::moveTo(long moveToPosition) {
  
  if (this->position > moveToPosition && this->position < this->moveToPosition2) {
    this->moveToPosition = this->position - 20;
    this->moveToPosition2 = moveToPosition;
    
  } else if (this->position < moveToPosition && this->position > this->moveToPosition2) {

    this->moveToPosition = this->position + 20;
    this->moveToPosition2 = moveToPosition;
    
  } else {
    if (!isRunning()) {
      this->stepInterval = START_INTERVAL;
      
      if (moveToPosition < this->position) {
        digitalWrite(dirPin, HIGH);
      } else {
        digitalWrite(dirPin, LOW);
      }
      
    }
    
    this->moveToPosition = moveToPosition;
    this->moveToPosition2 = moveToPosition;
    
  }

}

bool Stepper::isRunning() {
  return this->position != moveToPosition;
}

void Stepper::setMaxSpeed(float maxSpeed) {
  this->maxSpd = maxSpeed;
  this->maxStepInterval = 1000000.0f / maxSpeed;
  
  if (this->stepInterval < this->maxStepInterval) {
    this->stepInterval = this->maxStepInterval;
  }

}

float Stepper::maxSpeed() {
  
  return this->maxSpd;
}

void Stepper::setAcceleration(float ignore) {
  
}

void Stepper::run() {
  if (this->position == moveToPosition) {
    if (this->position != moveToPosition2) {
      moveToPosition = moveToPosition2;
      if (moveToPosition < position) {
        digitalWrite(dirPin, HIGH);
      } else {
        digitalWrite(dirPin, LOW);
      }
      
      this->stepInterval = START_INTERVAL;
      
    } else {
      return;
    }
  }

  unsigned long time = micros();
  unsigned long nextStepTime = lastStepTime + stepInterval;
  
  if (   ((nextStepTime >= lastStepTime) && ((time >= nextStepTime) || (time < lastStepTime)))
       || ((nextStepTime < lastStepTime) && ((time >= nextStepTime) && (time < lastStepTime)))) {
    
    digitalWrite(stepPin, HIGH);
  
    this->position += (this->position < moveToPosition) ? 1 : -1;
    
    lastStepTime = time;
    if ( abs(this->position - moveToPosition) < 20) {
      stepInterval += 10;
    } else if (stepInterval > this->maxStepInterval) {
      stepInterval -= 20;
    }
    
    digitalWrite(stepPin, LOW);
    
  }
  
}

