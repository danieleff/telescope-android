#ifndef UART_H
#define UART_H

#include <Arduino.h>

class UART  {
  public:
    void setup();
    void loop();
    
  private:
    String input;
    unsigned long lastTime;
    
    void parseInput();
};

#endif

