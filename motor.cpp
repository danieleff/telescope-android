#include "motor.h"
#include "astro.h"

byte tracking = TRACKING_OFF;
Stepper stepperHa(Stepper::DRIVER, 5/*step*/, 6/*dir*/); 
Stepper stepperDec(Stepper::DRIVER, 7/*step*/, 8/*dir*/); 
uint16_t topHaSpeed;
uint16_t topDecSpeed;


