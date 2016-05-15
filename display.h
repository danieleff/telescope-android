#ifndef DISPLAY_H
#define DISPLAY_H

#include <LiquidCrystal_I2C.h>

#include "time.h"
#include "motor.h";
#include "astro.h"

const byte SCREEN_HOME = 0;
const byte SCREEN_SELECT_STAR = 1;
const byte SCREEN_SELECT_PLANET = 2;
const byte SCREEN_SELECT_DSO = 3;

extern short selected;

class Display {
  public:
    Display(): lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE) {};
    void setup();
    void loop();
    void set_screen(byte new_screen);
    byte getScreen();
    void refresh();
    
  private:
    void homeLoop();
    void selectLoop();
    unsigned long last_lcd_millis;
    LiquidCrystal_I2C lcd;

};


#endif

