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

void Time::loop() {
  
}

int Time::getMillisFraction() {
  long now = this->getTimestamp();
  if (now != this->lastTime) {
    this->millisStart = millis();
    this->lastTime = now;
  }

  int ret = millis() - this->millisStart;
  if (ret > 1000) ret = 1000;
  return ret;
}

