#ifndef TIME_H
#define TIME_H

#include <RTClib.h>

class Time {
  public: 
    void setup();
    void loop();
    
    DateTime getTime();
    long getTimestamp();
    int getMillisFraction();
    
    void setTime(long time);
    
  private:
    RTC_Millis softwareRtc;
    long lastTime;
    int millisStart;
};

extern Time time;

#endif

