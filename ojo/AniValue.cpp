#include "AniValue.h"
#include <stdint.h>

AniValue::AniValue(int min, int max, int cur, int step_value, int mode) {
  _init_cur = cur;
  _cur = cur;
  _min = min;
  _max = max;
  if(step_value > 1){
  _step_value = step_value;
  }
  if(mode == 2){
    _add = -min;
  }
  if (_cur < _min) {
    _min = _cur;
  } 
  if (_cur > _max) {
    _max = _cur;
  }
}

int AniValue::getValue(){
  if(_mode != IDLE){
  if(millis() > _waited + _wait){
  switch(_mode){
    case LINEAR:
    if(_cur != _to){
      _cur += _step;
    }else{
      _mode = IDLE;
    }
    break;
    case PULSE:
    if(_cur != _to){
      _cur += _step;
    }else{
      if(_step > 0){
        setTarget(_val[0], _val[2]);
      }else{
        setTarget(_val[1], _val[2]);
      }
    }
    break;
    case LOOPUP:
      if(_cur <= _max){
        _cur += _step;
      }else{
        _cur = _min;
      setTarget(_max, _val[0]);
      }
    break;
    case LOOPDOWN:
      if(_cur >= _min){
        _cur += _step;
      }else{
        _cur = _max;
      setTarget(_min, _val[0]);
      }
    break;
  }
  _waited = millis();
  }
  }
  return clamp();
}
void AniValue::addValue(int v){
  _mode = LINEAR;
  setTarget(_cur + v, 50);
}
void AniValue::setValue(int v){
  _mode = IDLE;
  _cur = v;
}
void AniValue::setLinear(int to, int time){
  _mode = LINEAR;
  setTarget(to,time);
}
void AniValue::setLinear(int to){
  _mode = LINEAR;
  setTarget(to,abs(to-_cur));
}
void AniValue::setPulse(int min, int max, int time){
  _mode = PULSE;
  _val[0] = min;
  _val[1] = max;
  _val[2] = time;
  if(_cur < max){
  setTarget(max, time);
  }else{
  setTarget(min, time);
  }
}
void AniValue::setPulse(int time){
  _mode = PULSE;
  _val[0] = _min;
  _val[1] = _max;
  _val[2] = time;
  if(_cur < _min + ((_max - _min) / 2)){
  setTarget(_min, time);
  }else{
  setTarget(_max, time);
  }
}
void AniValue::loopUp(int time){
  _mode = LOOPUP;
  _val[0] = time;
  setTarget(_max, time);
}
void AniValue::loopDown(int time){
  _mode = LOOPDOWN;
  _val[0] = time;
  setTarget(_min, time);
}
void AniValue::setTarget(int to, int time){
  _to = to;
  if(_to < _min){
    _to = _min;
  }
  if(_to > _max){
    _to = _max;
  }
  _wait = time / abs(_cur - _to);
  if(_cur < _to){
    _step = _step_value;
  }else if (_cur > _to){
    _step = -_step_value;
  }
  _waited = millis();
}

int AniValue::clamp() {
  if (_cur < _min) {
    _cur = _min;
  } else if (_cur > _max) {
    _cur = _max;
  }
  return _cur - _add;
}
void AniValue::reset(){
  _mode = IDLE;
  _cur = _init_cur;
}