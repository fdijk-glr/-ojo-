#include "Servo.h"
#include <Adafruit_NeoPixel.h>
#include "AniValue.h"

class Eye{
  public:
  Eye(int x_pin, int y_pin, int btn_pin);
  void init();
  void animate();
  bool isReady();
  bool button();
  void setPixel(int h, int s, int v);   
  void moveEye(int side);
  void moveEye(int side, int time);
  void openEye(int deg);
  void openEye(int deg, int time);
  void setEye(int side, int deg);
  void setEye(int side, int deg, int time);
  void reset();   
  void motorsOn();
  void motorsOff();
  AniValue _h;
  AniValue _s;
  AniValue _v;
  AniValue _x_angle;
  AniValue _y_angle;
  private:
  void setReady();
  bool _ready = 0;
  int _btn;
  int _x_pin;
  int _y_pin;
  Servo x_axis;
  Servo y_axis;
  Adafruit_NeoPixel led;
  long _timer = 0;
  int _time = 10;
};
