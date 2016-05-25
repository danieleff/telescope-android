#ifndef ASTRO_H
#define ASTRO_H

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
  int type;
  int index;
  AstronomicalObject object;
};

enum CelectialType {
  STAR, DSO, PLANET
};

class AstronomyData {
  public:
    virtual long size(CelectialType type)=0;
    virtual AstronomicalObject get(CelectialType type, long index)=0;
};

class ProgmemAstronomyData: public AstronomyData {
  public:
    long size(CelectialType type);
    AstronomicalObject get(CelectialType type, long index);
};
class EpromAstronomyData: public AstronomyData {
  public:
    long size(CelectialType type);
    AstronomicalObject get(CelectialType type, long index);
};
class SDAstronomyData: public AstronomyData {
  public:
    long size(CelectialType type);
    AstronomicalObject get(CelectialType type, long index);
};

class Astronomy {
  public:
    void setData(AstronomyData *data);
    AstronomyData *getData();
    void loop();
    char* ra_to_string(double ra);
    char* dec_to_string(double dec);
    AstronomicalObjectSelected getSelected();
    void select(int type, int index, AstronomicalObject object);
    float getLocalSideralTime();
    float raToHa(float ra);
    float haToRa(float ra);
    
  private:
    AstronomyData *data;
    char* float_to_string(double value, bool isDeclincation);
    void print_2digits(char* str, int i);
    AstronomicalObjectSelected objectSelected;
};

extern Astronomy astronomy;

#endif

