#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include "Stepper.h"

const uint16_t steps_per_turn = 200;
const uint16_t gear_ratio = 200;
const uint8_t microstep = 1;

const float STEPPER_RA_TO_ARCMILLIS = 24.0f / steps_per_turn / gear_ratio / microstep;
const float STEPPER_DEC_TO_ARCMILLIS = 360.0f / steps_per_turn / gear_ratio / microstep;

const byte TRACKING_OFF=0;
const byte TRACKING_FOLLOW=1;
const byte TRACKING_MANUAL=2;

extern byte tracking;

extern Stepper stepperHa;
extern Stepper stepperDec;

extern uint16_t topHaSpeed;
extern uint16_t topDecSpeed;

#endif

