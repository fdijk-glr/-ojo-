#include "Eye.h"
#include <stdint.h>

Eye::Eye(int x_pin, int y_pin, int btn_pin)
  : led(1, 7, NEO_GRBW + NEO_KHZ800),
    _h(0, 65535, 2000, 10),
    _s(0, 255, 254),
    _v(0, 255, 127),
    _x_angle(0, 1000, 500, 2, 1000),
    _y_angle(0, 1000, 1000, 2, 1000) {
  _x_pin = x_pin;
  _y_pin = y_pin;
  _btn = btn_pin;
}

void Eye::init() {
  Serial.println("Initialize Eye");
  Serial.println("Starting LED");
  led.begin();  // INITIALIZE NeoPixel strip object (REQUIRED)
  led.show();   // Turn OFF all pixels ASAP
  led.setBrightness(220);

  Serial.println("Starting Motors");
  motorsOn();

  delay(500);
  Serial.println("Done");
}

bool Eye::isReady() {
  if (!_ready) {
    x_axis.write(1500);
    y_axis.write(2000);

    setPixel(1, 255, 255);

    if (button()) {
      Serial.println("Ready");
      setReady();
    }
  }
  return _ready;
}

bool Eye::button(){
  return digitalRead(_btn);
}

void Eye::setReady() {
  _ready = 1;
}

void Eye::animate() {
  x_axis.write(_x_angle.getValue());
  y_axis.write(_y_angle.getValue());
  // Serial.println(br);
  setPixel(_h.getValue(), _s.getValue(), _v.getValue());
  // led.show();
  if(_btn_wait){
    _btn_pressed = button();
    if(_btn_pressed){
      _btn_wait = false;
    }
  }
  // Serial.println("anim");
}

void Eye::setPixel(int h, int s, int v) {
  led.setPixelColor(0, led.ColorHSV(h, s, v));
  led.show();
}

void Eye::moveEye(int side) {
  _x_angle.setValue(side);
}
void Eye::moveEye(int side, int time) {
  _x_angle.setLinear(side, time);
}

void Eye::openEye(int spread) {
  _y_angle.setValue(spread);
}
void Eye::openEye(int spread, int time) {
  _y_angle.setLinear(spread, time);
}

void Eye::setEye(int side, int spread) {
  _x_angle.setValue(side);
  _y_angle.setValue(spread);
}
void Eye::setEye(int side, int spread, int time) {
  _x_angle.setLinear(side, time);
  _y_angle.setLinear(spread, time);
}

void Eye::reset() {
  _h.reset();
  _s.reset();
  _v.reset();
  _x_angle.reset();
  _y_angle.reset();
}

void Eye::motorsOn() {
  x_axis.attach(_x_pin);
  y_axis.attach(_y_pin);
}
void Eye::motorsOff() {
  x_axis.detach();
  y_axis.detach();
}
