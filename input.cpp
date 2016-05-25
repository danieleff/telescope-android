#include "input.h"
#include "motor.h"
#include "astro.h"
#include "display.h"

//TODO LCD, MOTOR
extern AstronomicalObject objectsToSelect[8];

extern Display display;

void Input::down(byte key) {

  if (display.getScreen() == SCREEN_HOME) {
    
    if (key == T_KEY_STOP) {
      tracking = TRACKING_OFF;
      display.refresh();
    } else if (key == T_KEY_FOLLOW) {
      tracking = TRACKING_FOLLOW;
      display.refresh();
    }
    
  } else if (display.getScreen() == SCREEN_CLEAR) {

    if (key == T_KEY_1) {
      motor.clearRa(0);
      display.set_screen(SCREEN_HOME);
    }
    if (key == T_KEY_2) {
      motor.clearDec(1);
      display.set_screen(SCREEN_HOME);
    }
    
  } else {
    if (key == T_KEY_OK) {
      astronomy.select(display.getScreen(), selected, objectsToSelect[selected]);
      
      display.set_screen(SCREEN_HOME);
    }
  
    if (key == T_KEY_UP) {
      selected -= 2;
    }
    if (key == T_KEY_DOWN) {
      selected += 2;
    }
    if (key == T_KEY_LEFT) {
      selected -= 1;
    }
    if (key == T_KEY_RIGHT) {
      selected += 1;
    }
    if (selected< 0) selected+=8;
    if (selected>=8) selected-=8;
    
  }
    
  if (key == T_KEY_STARS) {
    display.set_screen(SCREEN_SELECT_STAR);
  }
  if (key == T_KEY_DSOS) {
    display.set_screen(SCREEN_SELECT_DSO);
  }
  if (key == T_KEY_PLANETS) {
    display.set_screen(SCREEN_SELECT_PLANET);
  }
  if (key == T_KEY_CLEAR) {
    display.set_screen(SCREEN_CLEAR);
  }
  if (key == T_KEY_BACK) {
    display.set_screen(SCREEN_HOME);
  }

  this->hold(key);
}
void Input::hold(byte key) {

  /*
  if (screen == SCREEN_HOME) {
    if (key == T_KEY_UP) {
      
      stepper_ra.moveTo(stepper_ra.currentPosition() + stepper_ra.maxSpeed() );
      last_lcd_millis = 0;
    } else if (key == T_KEY_DOWN) {
      stepper_ra.moveTo(stepper_ra.currentPosition() - stepper_ra.maxSpeed() );
      last_lcd_millis = 0;
    } else if (key == T_KEY_LEFT) {
      stepper_dec.moveTo(stepper_dec.currentPosition() - stepper_ra.maxSpeed() );
      last_lcd_millis = 0;
    } else if (key == T_KEY_RIGHT) {
      stepper_dec.moveTo(stepper_dec.currentPosition() + stepper_ra.maxSpeed() );
      last_lcd_millis = 0;
    }
  }
  */
  
}

