#pragma once

#include "ofMain.h"

class ofxNoise {
  
public:
  float noise;
  float step;
  float max;
  float min;
  
  ofxNoise();
  void update();
  void setup(float _step, float _max);
  void setup(float _step, float _min, float _max);
  void setSpeed(float _step);
  void setRange(float _min, float _max);
  float getNoise();
  
};
