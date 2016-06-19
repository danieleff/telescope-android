#include "time.h"

void Time::setup() {
  
  softwareRtc.begin(DateTime(F(__DATE__), F(__TIME__)) - TimeSpan(0, 2, 0, 0)); //Adjusted for timezone
  
  hardwareExists = hardwareRtc.begin();
}

DateTime Time::getTime() {
  if (hardwareExists) {
    return this->hardwareRtc.now();
  } else {
    return this->softwareRtc.now();
  }
}

void Time::setTime(uint32_t time) {
  this->softwareRtc.adjust(time);
  if (hardwareExists) {
      this->hardwareRtc.adjust(time);
  }
}


uint16_t Time::getMillisFraction() {
  uint32_t now = this->getTime().unixtime();
  if (now != this->lastTime) {
    this->millisStart = millis();
    this->lastTime = now;
  }

  uint16_t ret = millis() - this->millisStart;
  if (ret > 1000) ret = 1000;
  return ret;
}

