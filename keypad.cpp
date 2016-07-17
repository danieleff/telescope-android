#include "keypad.h"
#include <arduino.h>

void Key::setup() {
  kpd.init();
}


void Key::loop() {
  char key = kpd.get_key();

  if(key != '\0') {
        Serial.print(key);
  }
}

