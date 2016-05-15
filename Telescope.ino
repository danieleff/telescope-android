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
}

void loop() {
  time.loop();
  motor.loop();
  joystick.loop();
  ir.loop();
  uart.loop();
  display.loop();
  astronomy.loop();
}

