#include "input.h"
#include "motor.h"
#include "astro.h"
#include "display.h"

//TODO LCD, MOTOR
extern AstronomicalObject objectsToSelect[8];

extern Display display;

void Input::key(byte k, bool d) {
  if (d) {
    down(k);
  } else {
    hold(k);
  }
}

void Input::down(byte key) {
  byte screen = display.getScreen();
  
  bool reload_objects = false;
  
  if (screen == SCREEN_HOME) {
    
    if (key == T_KEY_STOP) {
      tracking = TRACKING_OFF;
      display.refresh();
    } else if (key == T_KEY_FOLLOW) {
      tracking = TRACKING_FOLLOW;
      display.refresh();
    }
    
  } else if (screen == SCREEN_CLEAR) {

    if (key == T_KEY_1) {
      stepperHa.setCurrentPosition(0);
      display.setScreen(SCREEN_HOME);
    }
    if (key == T_KEY_2) {
      stepperDec.setCurrentPosition(0);
      display.setScreen(SCREEN_HOME);
    }
    
  } else if (screen == SCREEN_SELECT) {
    if (key == T_KEY_OK) {
      astronomy.select(display.getSelectedType(), display.getSelectedIndex(), objectsToSelect[display.getSelectedIndex() % 8]);
      
      display.setScreen(SCREEN_HOME);
    }

    int index = display.getSelectedIndex();
    
    if (key == T_KEY_UP) {
      index -= 2;
    }
    if (key == T_KEY_DOWN) {
      index += 2;
    }
    if (key == T_KEY_LEFT) {
      index -= 1;
    }
    if (key == T_KEY_RIGHT) {
      index += 1;
    }
    if (key == T_KEY_PGUP) {
      index -= 8;
    }
    if (key == T_KEY_PGDOWN) {
      index += 8;
    }
    //if (key == T_KEY_0) {
    //  index += 0;
    //}
    if (index <  0) index = 0;
    //if (index >= 1000) index-= 1000;

    reload_objects = true;
    display.setSelectedIndex(index);
    
  }
  
  if (key == T_KEY_STARS) {
    display.setScreen(SCREEN_SELECT, CELESTIAL_STAR);
    reload_objects = true;
  }
  if (key == T_KEY_DSOS) {
    display.setScreen(SCREEN_SELECT, CELESTIAL_DSO);
    reload_objects = true;
  }
  if (key == T_KEY_PLANETS) {
    display.setScreen(SCREEN_SELECT, CELESTIAL_PLANET);
    reload_objects = true;
  }

  if (reload_objects) {
    uint8_t type = display.getSelectedType();
    
    for(int i=0;i<8;i++) {
      objectsToSelect[i] = astronomy.getData()->get(type, i + (display.getSelectedIndex() / 8) * 8);
    }
  }
  
  if (key == T_KEY_CLEAR) {
    display.setScreen(SCREEN_CLEAR);
  }
  if (key == T_KEY_BACK) {
    display.setScreen(SCREEN_HOME);
  }

  this->hold(key);
}

void Input::hold(byte key) {

  if (display.getScreen() == SCREEN_HOME) {
    if (key == T_KEY_UP) {
      
      stepperHa.moveTo(stepperHa.currentPosition() - stepperHa.maxSpeed() * 0.15);
      
    } else if (key == T_KEY_DOWN) {
      
      stepperHa.moveTo(stepperHa.currentPosition() + stepperHa.maxSpeed() * 0.15);
      
    } else if (key == T_KEY_LEFT) {
      
      stepperDec.moveTo(stepperDec.currentPosition() - stepperDec.maxSpeed() * 0.15);
      
    } else if (key == T_KEY_RIGHT) {
      
      stepperDec.moveTo(stepperDec.currentPosition() + stepperDec.maxSpeed() * 0.15);
      
    }
  }
  
  
}

