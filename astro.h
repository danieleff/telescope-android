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

extern const AstronomicalObject stars[] PROGMEM;
extern const AstronomicalObject dsos[] PROGMEM;
extern const AstronomicalObject planets[] PROGMEM;
extern const AstronomicalObjectTime planetsTime[] PROGMEM;
extern const short planetMeta[];
extern const float planetStartJulian;
extern const long planetStartSeconds;

class Astronomy {
  public:
    void loop();
    char* ra_to_string(double ra);
    char* dec_to_string(double dec);
    AstronomicalObjectSelected getSelected();
    void select(int type, int index, AstronomicalObject object);
    float getLocalSideralTime();
    float raToHa(float ra);
    float haToRa(float ra);
    
  private:
    
    char* float_to_string(double value, bool isDeclincation);
    void print_2digits(char* str, int i);
    AstronomicalObjectSelected objectSelected;
};

extern Astronomy astronomy;

#endif

