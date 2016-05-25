#include "ir.h"

void IR::setup()
{
  this->irrecv.enableIRIn(); // Start the receiver
  //irrecv.blink13(true);

  pinMode(8, OUTPUT);
}



void IR::loop() {
  
  if (this->irrecv.decode(&results)) {
    

    if (millis() - this->previous > 200) {

      switch(this->results.value) {
        case IR_UP    : this->down(T_KEY_UP);break;
        case IR_DOWN  : this->down(T_KEY_DOWN);break;
        case IR_LEFT  : this->down(T_KEY_LEFT);break;
        case IR_RIGHT : this->down(T_KEY_RIGHT);break;
        case IR_BACK  : this->down(T_KEY_BACK);break;
        case IR_OK    : this->down(T_KEY_OK);break;
        case IR_STOP  : this->down(T_KEY_STOP);break;
        case IR_PLAY  : this->down(T_KEY_FOLLOW);break;
        
        case IR_RED   : this->down(T_KEY_STARS);break;
        case IR_GREEN : this->down(T_KEY_DSOS);break;
        case IR_YELLOW: this->down(T_KEY_PLANETS);break;

        case IR_0: this->down(T_KEY_CLEAR);break;
        case IR_RECORD: this->down(T_KEY_RECORD);break;
        case IR_1: this->down(T_KEY_1);break;
        case IR_2: this->down(T_KEY_2);break;
      }
      
    } else {

      Serial.println(this->results.value, HEX);
      
      switch(this->results.value) {
        case IR_UP    : this->hold(T_KEY_UP);break;
        case IR_DOWN  : this->hold(T_KEY_DOWN);break;
        case IR_LEFT  : this->hold(T_KEY_LEFT);break;
        case IR_RIGHT : this->hold(T_KEY_RIGHT);break;
        case IR_BACK  : this->hold(T_KEY_BACK);break;
        case IR_OK    : this->hold(T_KEY_OK);break;
        case IR_STOP  : this->hold(T_KEY_STOP);break;
        case IR_PLAY  : this->hold(T_KEY_FOLLOW);break;
        
        case IR_RED   : this->hold(T_KEY_STARS);break;
        case IR_GREEN : this->hold(T_KEY_DSOS);break;
        case IR_YELLOW: this->hold(T_KEY_PLANETS);break;

        case IR_0: this->hold(T_KEY_CLEAR);break;
        case IR_RECORD: this->hold(T_KEY_RECORD);break;
        case IR_1: this->hold(T_KEY_1);break;
        case IR_2: this->hold(T_KEY_2);break;
        
      }
    }

    
    this->irrecv.resume();
    this->previous = millis();
    
  }
  
}

