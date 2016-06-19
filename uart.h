#ifndef UART_H
#define UART_H

#include <Arduino.h>

#define BUFFER_MAX 24

class UART  {
  public:
    void setup();
    void loop();
    
  private:
    char buffer[BUFFER_MAX];
    uint8_t buffer_index;
    
    unsigned long lastTime;
    
    void parseInput();
};

#endif

