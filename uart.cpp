#include "uart.h"
#include "astro.h"
#include "display.h"
#include "time.h"
#include "motor.h"

void UART::setup() {
  Serial.begin(115200);
  buffer_index=0;
}

void UART::loop() {
  while (Serial.available() > 0)
    {
        char recieved = Serial.read();
        buffer[buffer_index] = recieved;
        buffer_index++;

        if (recieved == '\n' || buffer_index >= BUFFER_MAX) {
          buffer[buffer_index] = 0;
          
          this->parseInput();
          buffer_index = 0;
        }
    }
    

    if (millis() - this->lastTime > 50) {
      this->lastTime = millis();
      Serial.print("Pos ");
      Serial.print(astronomy.haToRa(stepperHa.currentPosition() * STEPPER_RA_TO_ARCMILLIS), 6);
      Serial.print(" ");
      Serial.print(stepperDec.currentPosition() * STEPPER_DEC_TO_ARCMILLIS, 6);
      Serial.println();
    }
    
}


void UART::parseInput() {

  if (strncmp(buffer, "Move", 4) == 0) {

    float ra;
    float dec;

    memcpy(&ra, buffer + 4, 4);
    memcpy(&dec, buffer + 8, 4);
    
    AstronomicalObject obj;
    strcpy(obj.name, "Serial");
    obj.ra = ra;
    obj.dec = dec;
    astronomy.select(CELESTIAL_STAR, 0, obj);
    
  } else if (strncmp(buffer, "Time", 4) == 0) {

    time.setTime(atol(buffer + 5));
    
  }
}


