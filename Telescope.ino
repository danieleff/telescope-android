#include "t_keypad.h"

#include "astro.h"
#include "time.h"
#include "joystick.h"
#include "motor.h"
#include "uart.h"
#include "ir.h"
#include "display.h"
#include "keypad.h"

Time time;
Astronomy astronomy;
Display display;

Joystick joystick;
IR ir;
UART uart;
Key key;

void setup() {  
  time.setup();
  key.setup();
  
  stepperHa.setMaxSpeed(1800.0);
  stepperHa.setAcceleration(6000.0);
  stepperDec.setMaxSpeed(1800.0);
  stepperDec.setAcceleration(6000.0);
  topHaSpeed = stepperHa.maxSpeed();
  topDecSpeed = stepperDec.maxSpeed();
  noInterrupts();
  TCCR1A = 0;// set entire TCCR2A register to 0
  TCCR1B = 0;// same for TCCR2B
  TCNT1  = 0;//initialize counter value to 0
  
  // set compare match register for 8khz increments
  OCR1A = 249;// = (16*10^6) / (8000*8) - 1 (must be <256)
  
  // turn on CTC mode
  TCCR1A |= (1 << WGM11);
  // Set CS21 bit for 8 prescaler
  TCCR1B |= (1 << CS11);
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  interrupts();
  
  
  joystick.setup();
  ir.setup();
  uart.setup();
  display.setup();
  
  //astronomy.setData(new ProgmemAstronomyData());
  astronomy.setData(new SDAstronomyData());
}

void loop() {
  
  joystick.loop();
  ir.loop();
  key.loop();
  display.loop();
  uart.loop();
  astronomy.loop();
  
  AstronomicalObjectSelected objectSelected = astronomy.getSelected();
  if (tracking == TRACKING_FOLLOW && objectSelected.object.name[0]) {
    stepperHa.moveTo(astronomy.raToHa(objectSelected.object.ra) / STEPPER_RA_TO_ARCMILLIS);
    stepperDec.moveTo(objectSelected.object.dec / STEPPER_DEC_TO_ARCMILLIS);
  }
  
}

ISR(TIMER1_COMPA_vect) {
  stepperHa.run();
  stepperDec.run();
}



