#ifndef IR_H
#define IR_H

#include <IRremote.h>

#include "input.h"

const uint32_t IR_UP = 0xCB052CC8;
const uint32_t IR_DOWN = 0xA402B0CE;
const uint32_t IR_LEFT = 0x57F0D80F;
const uint32_t IR_RIGHT = 0xEAA5D43C;
const uint32_t IR_BACK = 0xBEBB0CFA;
const uint32_t IR_MENU = 0xDC1387E2;
const uint32_t IR_OK = 0xDE272CB6;

const uint32_t IR_STOP = 0x98519C65;
const uint32_t IR_PLAY = 0xAFAF8374;
const uint32_t IR_RECORD = 0xE5BD88F4;

const uint32_t IR_RED = 0xF21D7D46;
const uint32_t IR_GREEN = 0x87CF1B29;
const uint32_t IR_YELLOW = 0x6623D37C;
const uint32_t IR_BLUE = 0x854115F2;

const uint32_t IR_0 = 0x7EC02B57;
const uint32_t IR_1 = 0xA669A2AA;
const uint32_t IR_2 = 0x407B03BD;
const uint32_t IR_3 = 0xBC6836D6;
const uint32_t IR_4 = 0xC2A56EBC;
const uint32_t IR_5 = 0xE7A7E794;
const uint32_t IR_6 = 0x85BEBE9B;
const uint32_t IR_7 = 0x5C917422;
const uint32_t IR_8 = 0x9BC33789;
const uint32_t IR_9 = 0xE4E4282C;

const uint32_t IR_CHANNEL_PLUS = 0x276C161A;
const uint32_t IR_CHANNEL_MINUS = 0x6852CC8B;


const int RECV_PIN = 9;

class IR : Input {
  public:
    IR(): irrecv(RECV_PIN) {};
    void setup();
    void loop();
    
  private:
    IRrecv irrecv;
    unsigned long previous = 0;

};

#endif

