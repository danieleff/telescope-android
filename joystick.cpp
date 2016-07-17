#include "joystick.h"
#include "motor.h"

void Joystick::setup() {
  
}

void Joystick::loop() {
  
  int x = analogRead(A2);

  float newMax = topHaSpeed;
  float newMoveTo = stepperHa.currentPosition();
  
  if (x < 512 - 80) {    
    newMax *=  (512 - x) / 512.0f;
    newMoveTo += newMax * 0.3;    
    joystickXUsed = true;
    
  } else if (x > 512 + 80) {    
    newMax *=  (x - 512) / 512.0f;
    newMoveTo -=  newMax * 0.3;
    joystickXUsed = true;
  } 
  
  if (joystickXUsed) {
    if (!stepperHa.isRunning()) {
      joystickXUsed = false;
    }
    
    stepperHa.setMaxSpeed(newMax);
    stepperHa.moveTo(newMoveTo);
  }


  x = analogRead(A3);
  newMax = topDecSpeed;
  newMoveTo = stepperDec.currentPosition();
  
  if (x < 512 - 80) {
    newMax *= (512 - x) / 512.0f;
    newMoveTo += newMax * 0.3;
    joystickYUsed = true;    
  } else if (x > 512 + 80) {    
    newMax *= (x - 512) / 512.0f;
    newMoveTo -= newMax * 0.3;
    joystickYUsed = true;    
  }
  
  if (joystickYUsed) {
    if (!stepperDec.isRunning()) {
      joystickYUsed = false;
    }
    
    stepperDec.setMaxSpeed(newMax);
    stepperDec.moveTo(newMoveTo);
  }
}

