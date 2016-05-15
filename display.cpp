#include "display.h"

AstronomicalObject objectsToSelect[8];

byte screen = SCREEN_HOME;

short selected = 0;

void Display::setup() {
  this->lcd.begin(20,4);
  last_lcd_millis=-1000;
}

void Display::refresh() {
  last_lcd_millis = 0;
}

void Display::set_screen(byte new_screen) {
  screen=new_screen;
  this->lcd.clear();
}

byte Display::getScreen() {
  return screen;
}

void Display::homeLoop() {
  this->lcd.setCursor(0, 0);
  this->lcd.print(astronomy.ra_to_string(astronomy.haToRa(motor.getHourAngle())));
  this->lcd.setCursor(0, 1);
  this->lcd.print(astronomy.dec_to_string(motor.getDeclination()));
   
  AstronomicalObjectSelected objectSelected = astronomy.getSelected();
  
  if (objectSelected.object.name[0]) {
    float ra = objectSelected.object.ra;
    float dec = objectSelected.object.dec;

    
    this->lcd.setCursor(0, 2);
    this->lcd.print(astronomy.ra_to_string(ra));
    //this->lcd20x4.print(objectSelected.index);
    this->lcd.setCursor(0, 3);
    this->lcd.print(astronomy.dec_to_string(dec));
    //lcd.print(planetMeta[objectSelected.index * 3 + 2]);
    
    

    String s(objectSelected.object.name);
    this->lcd.setCursor(14, 2);
    this->lcd.print(s.substring(0, 6).c_str());
    this->lcd.setCursor(14, 3);
    this->lcd.print(s.substring(6).c_str());
    
  } else {
    

    DateTime now = time.getTime();

    this->lcd.setCursor(0, 2);
    this->lcd.print(time.getTimestamp());
    
    this->lcd.setCursor(0, 3);
    this->lcd.print(now.year(), DEC);
    this->lcd.print('-');
    if (now.month()<10) lcd.print('0');
    this->lcd.print(now.month(), DEC);
    this->lcd.print('-');
    if (now.day()<10) lcd.print('0');
    this->lcd.print(now.day(), DEC);
    
    this->lcd.print(' ');
    if (now.hour()<10) lcd.print('0');
    this->lcd.print(now.hour(), DEC);
    this->lcd.print(':');
    if (now.minute()<10) lcd.print('0');
    this->lcd.print(now.minute(), DEC);
    this->lcd.print(':');
    if (now.second()<10) lcd.print('0');
    this->lcd.print(now.second(), DEC);
  }

  lcd.setCursor(14, 0);
  if (tracking == TRACKING_OFF) {
    this->lcd.print(F("   OFF"));
  } else if (tracking == TRACKING_FOLLOW) {
    this->lcd.print(F("FOLLOW"));
  } else if (tracking == TRACKING_MANUAL) {
    this->lcd.print(F("MANUAL"));
  }
}

void Display::selectLoop() {

  if (screen == SCREEN_SELECT_STAR) {
    memcpy_P(&objectsToSelect, &stars[0], sizeof(objectsToSelect));
  } else if (screen == SCREEN_SELECT_DSO) {
    memcpy_P(&objectsToSelect, &dsos[0], sizeof(objectsToSelect));
  } else {
    memcpy_P(&objectsToSelect, &planets[0], sizeof(objectsToSelect));
  }
  
  this->lcd.setCursor(1, 0);
  this->lcd.print(objectsToSelect[0].name);
  this->lcd.setCursor(11, 0);
  this->lcd.print(objectsToSelect[1].name);
  this->lcd.setCursor(1, 1);
  this->lcd.print(objectsToSelect[2].name);
  this->lcd.setCursor(11, 1);
  this->lcd.print(objectsToSelect[3].name);
  this->lcd.setCursor(1, 2);
  this->lcd.print(objectsToSelect[4].name);
  this->lcd.setCursor(11, 2);
  this->lcd.print(objectsToSelect[5].name);
  
  this->lcd.setCursor(1, 3);
  this->lcd.print(objectsToSelect[6].name);
  this->lcd.setCursor(11, 3);
  this->lcd.print(objectsToSelect[7].name);

  for(int i=0;i<8;i++) {
    this->lcd.setCursor((i % 2) * 10, (i / 2));
    if (i == selected) {
      this->lcd.print('>');
    } else {
      this->lcd.print(' ');
    }
  }
  
}

void Display::loop() {
  if (millis()-this->last_lcd_millis > 100) {
    
    if (screen == SCREEN_HOME) {
      this->homeLoop();
    } else if (screen == SCREEN_SELECT_STAR
      || screen == SCREEN_SELECT_PLANET
      || screen == SCREEN_SELECT_DSO) {
      this->selectLoop();
    }
    this->last_lcd_millis = millis();
  }
}

