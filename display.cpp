#include "display.h"

AstronomicalObject objectsToSelect[8];

void Display::setup() {
  
  this->lcd.begin(20,4);
  last_lcd_millis=-1000;
  screen = SCREEN_HOME;
}

void Display::refresh() {
  last_lcd_millis = 0;
}

void Display::clear() {
  this->lcd.clear();
}

void Display::setScreen(uint8_t screen) {
  this->screen = screen;
  this->lcd.clear();
}
void Display::setScreen(uint8_t screen, uint8_t celestialType) {
  this->screen = screen;
  this->celestialType = celestialType;
  this->lcd.clear();
}

byte Display::getScreen() {
  return screen;
}

void Display::setSelectedIndex(uint16_t selectedIndex) {
  this->selectedIndex = selectedIndex;
}

uint16_t Display::getSelectedIndex() {
  return selectedIndex;
}

uint8_t Display::getSelectedType() {
  return celestialType;
}

void Display::print(uint8_t x, uint8_t y, const char* str) {
  lcd.setCursor(x, y);
  lcd.print(str);
}
/*
void Display::printMin2Digits(uint8_t x, uint8_t y, int i) {
  lcd.setCursor(x, y);
  if (i<10) lcd.print('0');
  lcd.print(i);
}*/

void Display::homeLoop() {
  print(0, 0, astronomy.ra_to_string(astronomy.haToRa(stepperHa.currentPosition() * STEPPER_RA_TO_ARCMILLIS)));
  print(0, 1, astronomy.dec_to_string(stepperDec.currentPosition() * STEPPER_DEC_TO_ARCMILLIS));
   
  AstronomicalObjectSelected objectSelected = astronomy.getSelected();
  
  if (objectSelected.object.name[0]) {
    float ra = objectSelected.object.ra;
    float dec = objectSelected.object.dec;


    print(0, 2, astronomy.ra_to_string(ra));
    print(0, 3, astronomy.dec_to_string(dec));

    this->lcd.setCursor(14, 2);
    this->lcd.write(objectSelected.object.name, 6);
    
    print(14, 3, objectSelected.object.name + 6);
    
  } else {
    

    DateTime now = time.getTime();
    
    this->lcd.setCursor(0, 3);
    this->lcd.print(now.year());
    this->lcd.print('-');
    if (now.month()<10) lcd.print('0');
    this->lcd.print(now.month());
    this->lcd.print('-');
    if (now.day()<10) lcd.print('0');
    this->lcd.print(now.day());
    
    this->lcd.print(' ');
    if (now.hour()<10) lcd.print('0');
    this->lcd.print(now.hour());
    this->lcd.print(':');
    if (now.minute()<10) lcd.print('0');
    this->lcd.print(now.minute());
    this->lcd.print(':');
    if (now.second()<10) lcd.print('0');
    this->lcd.print(now.second());
    
  }
/*
  lcd.setCursor(14, 0);
  if (tracking == TRACKING_OFF) {
    this->lcd.print("   OFF");
  } else if (tracking == TRACKING_FOLLOW) {
    this->lcd.print("FOLLOW");
  } else if (tracking == TRACKING_MANUAL) {
    this->lcd.print("MANUAL");
  }*/
}

void Display::selectLoop() {

  for(int i=0;i<8;i++) {
    print((i % 2) * 10, (i / 2), (i == selectedIndex % 8) ? ">": " ");
    print(1 + (i % 2) * 10, i / 2, objectsToSelect[i].name);
  }
  
}

void Display::loopClear() {
  /*
  this->lcd.setCursor(0, 0);
  this->lcd.print(F("1. Set Ra to 0"));
  
  this->lcd.setCursor(0, 1);
  this->lcd.print(F("2. Set Dec to 0"));

  this->lcd.setCursor(0, 2);
  this->lcd.print(F("3. Clear first star"));

  this->lcd.setCursor(0, 3);
  this->lcd.print(F("4. Clear second star"));
  */
}

void Display::loop() {
  if (millis()-this->last_lcd_millis > 100) {
    
    if (screen == SCREEN_HOME) {
      this->homeLoop();
    } else if (screen == SCREEN_SELECT) {
      this->selectLoop();
    } else if (screen == SCREEN_CLEAR) {
      this->loopClear();
    }
    this->last_lcd_millis = millis();
  }
}


