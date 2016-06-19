#include "ir.h"

void IR::setup()
{
  this->irrecv.enableIRIn(); // Start the receiver
  //irrecv.blink13(true);
}

void IR::loop() {
  
  decode_results results;
  
  if (this->irrecv.decode(&results)) {

    bool down;
    
    if (millis() - this->previous > 200) {
      down = true;
    } else {
      down = false;
    }

    switch(results.value) {
      case IR_UP    : this->key(T_KEY_UP, down);break;
      case IR_DOWN  : this->key(T_KEY_DOWN, down);break;
      case IR_LEFT  : this->key(T_KEY_LEFT, down);break;
      case IR_RIGHT : this->key(T_KEY_RIGHT, down);break;
      case IR_BACK  : this->key(T_KEY_BACK, down);break;
      case IR_OK    : this->key(T_KEY_OK, down);break;
      case IR_STOP  : this->key(T_KEY_STOP, down);break;
      case IR_PLAY  : this->key(T_KEY_FOLLOW, down);break;
      
      case IR_RED   : this->key(T_KEY_STARS, down);break;
      case IR_GREEN : this->key(T_KEY_DSOS, down);break;
      case IR_YELLOW: this->key(T_KEY_PLANETS, down);break;

      case IR_0: this->key(T_KEY_CLEAR, down);break;
      case IR_RECORD: this->key(T_KEY_RECORD, down);break;
      case IR_1: this->key(T_KEY_1, down);break;
      case IR_2: this->key(T_KEY_2, down);break;
      
      case IR_CHANNEL_PLUS: this->key(T_KEY_PGDOWN, down);break;
      case IR_CHANNEL_MINUS: this->key(T_KEY_PGUP, down);break;
      
    }
    
    this->irrecv.resume();
    this->previous = millis();
    
  }
  
}

