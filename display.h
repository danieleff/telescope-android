#ifndef DISPLAY_H
#define DISPLAY_H

#include <LiquidCrystal_I2C.h>

#include "time.h"
#include "motor.h";
#include "astro.h"

const byte SCREEN_HOME = 1;
const byte SCREEN_SELECT = 2;
const byte SCREEN_CLEAR = 3;
const byte SCREEN_SET = 4;

class Display {
  public:
    Display(): lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE) {};
    void setup();
    void loop();
    void setScreen(uint8_t screen);
    void setScreen(uint8_t screen, uint8_t celestialType);
    uint8_t getSelectedType();
    
    void setSelectedIndex(uint16_t selectedIndex);
    uint16_t getSelectedIndex();
    
    byte getScreen();
    void refresh();
    void clear();
    
  private:
    LiquidCrystal_I2C lcd;
    uint32_t last_lcd_millis;
    uint8_t screen;
    uint8_t celestialType;
    uint16_t selectedIndex;
    
    void print(uint8_t x, uint8_t y, const char* str);
    void homeLoop();
    void selectLoop();
    void loopClear();

};


#endif

