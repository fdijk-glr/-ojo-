#include <Arduino.h>

#define IDLE 0
#define LINEAR 1
#define PULSE 2
#define LOOPUP 3
#define LOOPDOWN 4


class AniValue{
  public:
  AniValue(int min, int max, int cur);
  AniValue(int min, int max, int cur, int step_value);
  int getValue();
  void addValue(int v);
  void setValue(int v);
  void setLinear(int to, int time);
  void setLinear(int to);
  void setPulse(int min, int max, int time);
  void setPulse(int time); //uses internal min & max
  void loopUp(int time);
  void loopDown(int time);
  void reset();
  private:
  int _mode = IDLE;
  int clamp();
  int _init_cur;
  int _cur;
  int _to;
  int _min;
  int _max;
  int _step;
  int _step_value = 1;
  int _wait = 10;
  long _waited = 0;
  int _val[3];
  void setTarget(int to, int time);
};