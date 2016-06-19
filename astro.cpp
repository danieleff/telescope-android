#include <Arduino.h>

#include "astro.h"
#include "time.h"
#include "display.h"
/*
#include "generated/stars.h"
#include "generated/dsos.h"
#include "generated/planets.h"
*/

#define header_bytes (4 * 6)

SDAstronomyData::SDAstronomyData() {
   
  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
  }
  
  file = SD.open("telesc~1/astron~1.bin");
  file.read(&meta, sizeof(meta));

  seek_star = sizeof(meta);
  seek_dso = seek_star + meta.stars * sizeof(AstronomicalObject);
  seek_planet = seek_dso + meta.dsos * sizeof(AstronomicalObject);
  seek_planet_time = seek_planet + meta.planets * sizeof(AstronomicalObject);
}

long SDAstronomyData::size(uint8_t type) {
  return 0;
}

AstronomicalObject SDAstronomyData::get(uint8_t type, uint16_t index) {
  AstronomicalObject ret = {0, 0, ""};
  
  long seek;
  
  if (type == CELESTIAL_STAR) {
    if (index >= meta.stars) {
      return ret;
    }
    
    seek = seek_star;
  } else if (type == CELESTIAL_DSO) {
    if (index >= meta.dsos) {
      return ret;
    }
    
    seek = seek_dso;
  } else if (type == CELESTIAL_PLANET) {
    if (index >= meta.planets) {
      return ret;
    }
    
    seek = seek_planet;
  }

  seek += index * sizeof(AstronomicalObject);
  
  if (file) {
    file.seek(seek);
    file.read(&ret, sizeof(ret));

    if (type == CELESTIAL_PLANET) {
      long unix_1970_seconds = time.getTime().unixtime();
        
      long delta = unix_1970_seconds - meta.planetTimeStart;
      float index = (float)delta / (meta.planetInterpolateDeltaMinutes * 60);
      //TODO 0 < x < meta
      float fraction = index - floor(index);

      AstronomicalObjectTime interpolate1, interpolate2;

      file.seek(seek_planet_time + ((int)floor(index)    ) * sizeof(AstronomicalObjectTime));
      file.read(&interpolate1, sizeof(interpolate1));
      file.read(&interpolate2, sizeof(interpolate2));
    
      ret.ra = interpolate1.ra * (1 - fraction) + interpolate2.ra * fraction;
      ret.dec = interpolate1.dec * (1 - fraction) + interpolate2.dec * fraction;
    }

  }
  
  return ret;
}
/*
long ProgmemAstronomyData::size(CelectialType type) {
  return 0;
}
AstronomicalObject ProgmemAstronomyData::get(CelectialType type, long index) {
  
  AstronomicalObject ret;
  if (type == STAR) {
    memcpy_P(&ret, &stars[index], sizeof(ret));
  } else if (type == DSO) {
    memcpy_P(&ret, &dsos[index], sizeof(ret));
  } else if (type == PLANET) {
    memcpy_P(&ret, &planets[index], sizeof(ret));

    long unix_1970_seconds = time.getTimestamp();
      
    long delta = unix_1970_seconds - planetStartSeconds;
    float x = (float)delta / (planetMeta[index * 3 + 1] * 60 * 60);
    //TODO 0 < x < meta
    float y = x - floor(x);
  
    AstronomicalObjectTime interpolate1, interpolate2;
  
    memcpy_P(&interpolate1, &planetsTime[(int)floor(x) + planetMeta[index * 3 + 2]], sizeof(interpolate1));
    memcpy_P(&interpolate2, &planetsTime[(int)floor(x) + 1 + planetMeta[index * 3 + 2]], sizeof(interpolate2));
  
    ret.ra = interpolate1.ra * (1 - y) + interpolate2.ra * y;
    ret.dec = interpolate1.dec * (1 - y) + interpolate2.dec * y;
  }
  return ret;
}
    */

void Astronomy::setData(AstronomyData *data) {
  this->data = data;
}

AstronomyData *Astronomy::getData() {
  return data;
}

void Astronomy::loop() {
  if (this->objectSelected.type == CELESTIAL_PLANET) {
    objectSelected.object = this->getData()->get(CELESTIAL_PLANET, this->objectSelected.index);
  }
}

char* Astronomy::ra_to_string(float ra) {
  return this->float_to_string(ra, false);
}

char* Astronomy::dec_to_string(float d) {
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
  
  long ut1_2000_seconds_minus_2016 = time.getTime().unixtime() - 946728000L - ut1_2016_may_seconds;
  float greenwich_mean_sideral_time = 0.00027853830815299861 * ut1_2000_seconds_minus_2016;
  greenwich_mean_sideral_time += 0.00027853830815299861 * time.getMillisFraction() / 1000;
  
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

void Astronomy::select(uint8_t type, int index, AstronomicalObject object) {
  this->objectSelected.type = type;
  this->objectSelected.index = index;
  this->objectSelected.object = object;
}

void Astronomy::print_2digits(char* str, int i) {
    str[0] = ((char)(i/10)%10) + '0';
    str[1] = ((char)(i%10)) + '0';
}

char* Astronomy::float_to_string(float value, bool isDeclincation) {
    static char buffer[14];

    
    if (isDeclincation) {
      buffer[3] = (char)223;
      buffer[6] = '\'';
      buffer[12] = '"';
    } else {
      buffer[3] = 'h';
      buffer[6] = 'm';
      buffer[12] = 's';
    }
    buffer[9] = '.';

    if (value <= 0) {
      value =-value;
      buffer[0]='-';
    } else {
      buffer[0]='+';
    }

    short degrees = floor(value);
    float degreesRemainder = value - degrees;
    
    short arcminutes = floor(degreesRemainder * 60);
    float arcminutesRemainder = degreesRemainder * 60 - arcminutes;

    short arcseconds = floor(arcminutesRemainder * 60);
    float arcsecondsRemainder = arcminutesRemainder * 60 - arcseconds;

    short arcmilliseconds_10 = floor(arcsecondsRemainder * 100);

    this->print_2digits(&buffer[1], degrees);
    
    this->print_2digits(&buffer[4], arcminutes);
    
    this->print_2digits(&buffer[7], arcseconds);
    
    this->print_2digits(&buffer[10], arcmilliseconds_10);
    
    return buffer;
}

