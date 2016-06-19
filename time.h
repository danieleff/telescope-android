#ifndef TIME_H
#define TIME_H

#include <RTClib.h>

class Time {
  public: 
    void setup();
    
    DateTime getTime();
    uint16_t getMillisFraction();
    
    void setTime(uint32_t time);
    
  private:
    RTC_Millis softwareRtc;
    RTC_DS1307 hardwareRtc;
    bool hardwareExists;
    long lastTime;
    int millisStart;
};

extern Time time;

#endif

