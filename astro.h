#ifndef ASTRO_H
#define ASTRO_H

#include <SD.h>

const uint8_t CELESTIAL_STAR = 0;
const uint8_t CELESTIAL_DSO = 1;
const uint8_t CELESTIAL_PLANET = 2;

struct AstronomicalObject {
  float ra;
  float dec;
  char name[10];
};

struct AstronomicalObjectTime {
  float ra;
  float dec;
};

struct AstronomicalObjectSelected {
  uint8_t type;
  int index;
  AstronomicalObject object;
};

struct AstronomyMeta {
  int32_t stars;
  int32_t dsos;
  int32_t planets;

  int32_t planetTimeStart;
  int32_t planetInterpolateCount;
  int32_t planetInterpolateDeltaMinutes;
};

class AstronomyData {
  public:
    virtual long size(uint8_t type)=0;
    virtual AstronomicalObject get(uint8_t type, uint16_t index)=0;
};

class ProgmemAstronomyData: public AstronomyData {
  public:
    long size(uint8_t type);
    AstronomicalObject get(uint8_t type, uint16_t index);
};

class EpromAstronomyData: public AstronomyData {
  public:
    long size(uint8_t type);
    AstronomicalObject get(uint8_t type, uint16_t index);
};

class SDAstronomyData: public AstronomyData {
  public:
    SDAstronomyData();
    long size(uint8_t type);
    AstronomicalObject get(uint8_t type, uint16_t index);
  
  private:
    File file;
    AstronomyMeta meta;
    long seek_star;
    long seek_dso;
    long seek_planet;
    long seek_planet_time;
};

class Astronomy {
  public:
    void setData(AstronomyData *data);
    AstronomyData *getData();
    void loop();
    char* ra_to_string(float ra);
    char* dec_to_string(float dec);
    AstronomicalObjectSelected getSelected();
    void select(uint8_t type, int index, AstronomicalObject object);
    float getLocalSideralTime();
    float raToHa(float ra);
    float haToRa(float ra);
    
  private:
    AstronomyData *data;
    char* float_to_string(float value, bool isDeclincation);
    void print_2digits(char* str, int i);
    AstronomicalObjectSelected objectSelected;
};

extern Astronomy astronomy;

#endif

