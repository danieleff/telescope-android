#include "joystick.h"
#include "motor.h"

void Joystick::setup() {
  
}

void Joystick::loop() {

  
  int x = analogRead(A0);
  if (x < 512 - 50) {
    
    motor.setHaMaxSpeedPercent((512 - x) / 512.0f);
    motor.moveToHourAngle(motor.getHourAngle() + motor.getMaxHaPerSecond() * 0.3);
    joystickXUsed = true;
    
  } else if (x > 512 + 50) {
    
    motor.setHaMaxSpeedPercent((x - 512) / 512.0f);
    motor.moveToHourAngle(motor.getHourAngle() - motor.getMaxHaPerSecond() * 0.3);
    joystickXUsed = true;
    
  } else if (joystickXUsed) {
    
    motor.moveToHourAngle(motor.getHourAngle());
    motor.setHaMaxSpeedPercent(1);
    joystickXUsed = false;
    
  }

  x = analogRead(A1);
  if (x < 512 - 50) {
  
    motor.setDecMaxSpeedPercent((512 - x) / 512.0f);
    motor.moveToDeclination(motor.getDeclination() + motor.getMaxDecPerSecond() * 0.3);
    joystickYUsed = true;
    
  } else if (x > 512 + 50) {
    
    motor.setDecMaxSpeedPercent((x - 512) / 512.0f);
    motor.moveToDeclination(motor.getDeclination() - motor.getMaxDecPerSecond() * 0.3);
    joystickYUsed = true;
    
  } else if (joystickYUsed) {
    
    motor.moveToDeclination(motor.getDeclination());
    motor.setDecMaxSpeedPercent(1);
    joystickYUsed = false;
    
  }
  
}

