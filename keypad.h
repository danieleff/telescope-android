#ifndef KEY_H
#define KEY_H

#include <i2ckeypad.h>
#define ROWS 4
#define COLS 4
// With A0, A1 and A2 of PCF8574 to ground I2C address is 0x20
#define PCF8574_ADDR 0x21

class Key {

  public:
    Key(): kpd(PCF8574_ADDR, ROWS, COLS) {};
    void setup();
    void loop();
    
  private:
    i2ckeypad kpd;
    
};

#endif KEY_H

