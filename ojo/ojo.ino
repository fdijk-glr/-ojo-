#include "Eye.h"

Eye eye(4,6,2);

long timer = 0;
long wait = 200;

int state = 0;

void setup() {
  //Begin USB communication
  Serial.begin(115200);
  //Initialize all Eye settings, needed to animate the eye
  eye.init();
}

void loop() {
  //stop loop at startup to construct the model
  //press button to continue
  if(!eye.isReady()){
    return;
  }
  //read serial data as number 0...10+
  if (Serial.available() > 0) {
    readSerial(Serial.parseInt());
  }
  //Timer to set custom animations while keeping the eye smooth
  if (millis() > timer + wait) {
    timer = millis();
    CustomAnimations();
  }
  //Animate the eye
  eye.animate();
}

void CustomAnimations() {
  // return;
  //Switch between animations per state
  Serial.println(state);
  switch (state) {
    case 0:
      eye._v.setLinear(254, 600);
      eye.setEye(1500,1000,600);
      wait = 1000;
      state++;
      break;
    case 1:
        eye._h.setPulse(300);
      // eye._x_angle.setLinear(2000, 600);
      // eye._y_angle.setLinear(1000, 600);
      eye._x_angle.setPulse(1000,2000, 2000);
      wait = 10000;
      state++;
      break;
    case 2:
      eye._v.setLinear(1, 600);
      eye._h.setValue(20000);
      eye.setEye(1500,2000,600);
      wait = 3000;
      state++;
      break;
    case 3:
      eye._v.setLinear(1, 600);
      eye._h.setValue(20000);
      eye._y_angle.setValue(2000);
      wait = 200;
      state++;
      break;
    case 4:
      eye._y_angle.setValue(1000);
      wait = 200;
      state++;
      break;
    case 5:
      eye._y_angle.setValue(2000);
      wait = 200;
      state++;
      break;
    default:
      state = 0;
      wait = 0;
      break;
  }
}

void readSerial(int num){
    Serial.println(num);
    switch (num) {
      case 1:
        eye._h.addValue(10);
        break;
      case 2:
        eye._h.addValue(-10);
        break;
      case 3:
        eye._h.setPulse(300);
        break;
      case 4:
        eye._s.addValue(10);
        break;
      case 5:
        eye._s.addValue(-10);
        break;
      case 6:
        eye._s.setPulse(300);
        break;
      case 7:
        eye._v.addValue(10);
        break;
      case 8:
        eye._v.addValue(-10);
        break;
      case 9:
        eye._v.setPulse(3000);
        break;
      case 0:
        eye.reset();
        break;
    }
}
