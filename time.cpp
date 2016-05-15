#include "time.h"

void Time::setup() {
  this->softwareRtc.begin(DateTime(F(__DATE__), F(__TIME__)) - TimeSpan(0, 2, 0, 0)); //Adjusted for timezone
}

DateTime Time::getTime() {
  return this->softwareRtc.now();
}

long Time::getTimestamp() {
  return this->softwareRtc.now().unixtime();
}

void Time::setTime(long time) {
  this->softwareRtc.adjust(time);
}

void  Time::loop() {
  
}

