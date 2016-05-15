#include <Arduino.h>

#include "astro.h"
#include "time.h"
#include "display.h"

#include "generated/stars.h"
#include "generated/dsos.h"
#include "generated/planets.h"

void Astronomy::loop() {
  if (this->objectSelected.type == SCREEN_SELECT_PLANET) {
      long unix_1970_seconds = time.getTimestamp();
      
      long delta = unix_1970_seconds - planetStartSeconds;
      float x = (float)delta / (planetMeta[objectSelected.index * 3 + 1] * 60 * 60);
      //TODO 0 < x < meta
      float y = x - floor(x);
  
      AstronomicalObject interpolate1, interpolate2;
  
      memcpy_P(&interpolate1, &planetsTime[(int)floor(x) + planetMeta[this->objectSelected.index * 3 + 2]], sizeof(interpolate1));
      memcpy_P(&interpolate2, &planetsTime[(int)floor(x) + 1 + planetMeta[this->objectSelected.index * 3 + 2]], sizeof(interpolate2));
  
      this->objectSelected.object.ra = interpolate1.ra * (1 - y) + interpolate2.ra * y;
      this->objectSelected.object.dec = interpolate1.dec * (1 - y) + interpolate2.dec * y;
  }
}

char* Astronomy::ra_to_string(double ra) {
  return this->float_to_string(ra, false);
}

char* Astronomy::dec_to_string(double d) {
  return this->float_to_string(d, true);
}

float Astronomy::raToHa(float ra) {
  return this->haToRa(ra);
}

float Astronomy::haToRa(float ha) {
  float ret = this->getLocalSideralTime() - ha;
  if (ret < 0) ret += 24;
  return ret;
}

float Astronomy::getLocalSideralTime() {
  //greenwich_mean_sideral_time_minus_2016 = (18.697374558 + 24.06570982441908 * UT1date) % 24;
  const long ut1_2016_may_seconds = 515325600L;//(int) (new DateTime(2016, 5, 1, 0, 0, 0).getMillis() / 1000 - 946728000);
  //double greenwich_mean_sideral_time_2016_may = (double) (18.697374558 + 0.00027853830815299861 * ut1_2000_seconds);
  const float may_delta = 12.618146486900514; // greenwich_mean_sideral_time_2016_may % 24;
  
  long ut1_2000_seconds_minus_2016 = time.getTimestamp() - 946728000L - ut1_2016_may_seconds;
  float greenwich_mean_sideral_time = 0.00027853830815299861 * ut1_2000_seconds_minus_2016;
  
  greenwich_mean_sideral_time += may_delta;
  greenwich_mean_sideral_time = fmod(greenwich_mean_sideral_time, 24);
  
  
  float longitude = 20.584497;
  float local_sideral_time = greenwich_mean_sideral_time + longitude / 15;
  local_sideral_time = fmod(local_sideral_time, 24);
  
  return local_sideral_time;
}

AstronomicalObjectSelected Astronomy::getSelected() {
  return this->objectSelected;
}

void Astronomy::select(int type, int index, AstronomicalObject object) {
  this->objectSelected.type = type;
  this->objectSelected.index = index;
  this->objectSelected.object = object;
}

void Astronomy::print_2digits(char* str, int i) {
    str[0] = ((char)(i/10)%10) + '0';
    str[1] = ((char)(i%10)) + '0';
}

char* Astronomy::float_to_string(double value, bool isDeclincation) {
    static char buffer[14]="+XX_YY_ZZ.ZZ_";
    
    //if (isDeclincation) {
    //  lcd.print(" ");
    //} else {
      if (value <= 0) {
        value =-value;
        buffer[0]='-';
      } else {
        buffer[0]='+';
      }
    //}

    short degrees = floor(value);
    double degreesRemainder = value - degrees;
    
    short arcminutes = floor(degreesRemainder * 60);
    double arcminutesRemainder = degreesRemainder * 60 - arcminutes;

    short arcseconds = floor(arcminutesRemainder * 60);
    double arcsecondsRemainder = arcminutesRemainder * 60 - arcseconds;

    short arcmilliseconds = floor(arcsecondsRemainder * 1000);

    
    this->print_2digits(&buffer[1], degrees);
    
    if (isDeclincation) {
      buffer[3]=(char)223;
    } else {
      buffer[3]='h';
    }
    
    this->print_2digits(&buffer[4], arcminutes);
    
    buffer[6] = isDeclincation ? '\'' : 'm';
    
    this->print_2digits(&buffer[7], arcseconds);
    
    buffer[9] = '.';
    
    this->print_2digits(&buffer[10], arcmilliseconds/10);
    
    buffer[12]=isDeclincation ? '"' : 's';

    return buffer;
}

