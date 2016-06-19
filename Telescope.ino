#include "t_keypad.h"

#include "astro.h"
#include "time.h"
#include "joystick.h"
#include "motor.h"
#include "uart.h"
#include "ir.h"
#include "display.h"

Time time;
Astronomy astronomy;
Display display;
Motor motor;
Joystick joystick;
IR ir;
UART uart;

void setup() {  
  time.setup();
  motor.setup(true);
  
  joystick.setup();
  ir.setup();
  uart.setup();
  display.setup();
  
  //astronomy.setData(new ProgmemAstronomyData());
  astronomy.setData(new SDAstronomyData());
  
}

void loop() {
  
  motor.loop();
  joystick.loop();
  ir.loop();
  display.loop();
  uart.loop();
  astronomy.loop();
}

