#include "uart.h"
#include "astro.h"
#include "display.h"
#include "time.h"
#include "motor.h"

void UART::setup() {
  Serial.begin(115200);
  Serial.setTimeout(100);
}

void UART::loop() {
  while (Serial.available() > 0)
    {
        char recieved = Serial.read();
        this->input += recieved; 

        if (recieved == '\n') {
          this->parseInput();
          input = "";
        }
    }
    

    if (millis() - this->lastTime > 50) {
      this->lastTime = millis();
      Serial.print("Pos ");
      Serial.print(astronomy.haToRa(motor.getHourAngle()), 6);
      Serial.print(" ");
      Serial.print(motor.getDeclination(), 6);
      Serial.println();
    }
    
}


void UART::parseInput() {
  if (this->input.startsWith("Move ")) {
    float ra = this->input.substring(5).toFloat();
    float dec = this->input.substring(input.indexOf(' ', 6)).toFloat();
    
    AstronomicalObject obj;
    strcpy(obj.name, "Serial");
    obj.ra = ra;
    obj.dec = dec;
    astronomy.select(SCREEN_SELECT_STAR, 1, obj);
    
  } else if (this->input.startsWith("Time ")) {

    time.setTime(this->input.substring(5).toInt());
    
  } else {
    //Serial.println(input.c_str());
  }
}


