/*
const byte KEYPAD_ROWS = 4; //four rows
const byte KEYPAD_COLS = 4; //three columns
char keys[KEYPAD_ROWS][KEYPAD_COLS] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'*','0','#', 'D'}
};

byte rowPins[KEYPAD_ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[KEYPAD_COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, KEYPAD_ROWS, KEYPAD_COLS );

bool is_pressed(char keyChar);

void keypad_home_loop(char key) {
  if (key == 'A') {
    set_screen(SCREEN_SELECT_STAR);
  }
  
  if (key == '*') {
    tracking = TRACKING_OFF;
    last_lcd_millis = 0;
  } else if (key == '0') {
    tracking = TRACKING_FOLLOW;
    last_lcd_millis = 0;
  } else if (key == '#') {
    tracking = TRACKING_MANUAL;
    last_lcd_millis = 0;
  }

  /*
  keypad.getKeys();
  if (is_pressed('2')) {
    stepper_ra.moveTo(stepper_ra.currentPosition() + STEP_DIR_KEYPAD);
    last_lcd_millis = 0;
  } else if (is_pressed('8')) {
    stepper_ra.moveTo(stepper_ra.currentPosition() - STEP_DIR_KEYPAD);
    last_lcd_millis = 0;
  } else if (is_pressed('4')) {
    stepper_dec.moveTo(stepper_dec.currentPosition() - STEP_DIR_KEYPAD);
    last_lcd_millis = 0;
  } else if (is_pressed('6')) {
    stepper_dec.moveTo(stepper_dec.currentPosition() + STEP_DIR_KEYPAD);
    last_lcd_millis = 0;
  } else {
    stepper_dec.moveTo(stepper_dec.currentPosition());
    stepper_ra.moveTo(stepper_ra.currentPosition());
    last_lcd_millis = 0;
  }
  * /
  
}

void keypad_select_loop(char key) {
  if (key == 'A') {
    set_screen(SCREEN_HOME);
  }
  if (key == 'B') {
    objectSelected.object = objectsToSelect[selected];
    set_screen(SCREEN_HOME);
  }

  if (key == '2') {
    selected -= 2;
  }
  if (key == '8') {
    selected += 2;
  }
  if (key == '4') {
    selected -= 1;
  }
  if (key == '6') {
    selected += 1;
  }
  if (selected< 0) selected+=8;
  if (selected>=8) selected-=8;
  
}

void keypad_loop() {
  char key = keypad.getKey();
  if (screen == SCREEN_HOME) {
    keypad_home_loop(key);
  } else {
    keypad_select_loop(key);
  }
}


bool is_pressed(char keyChar) {
  for (byte i=0; i<LIST_MAX; i++) {
    if ( keypad.key[i].kchar == keyChar ) {
      if (keypad.key[i].kstate == PRESSED || keypad.key[i].kstate == HOLD)
        return true;
    }
  }
  return false; // Not pressed.
}

*/

