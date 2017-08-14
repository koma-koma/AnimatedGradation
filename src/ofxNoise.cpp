//
//  ofxNoise.cpp
//  animatingGradation
//
//  Created by Miyashita Keita on 2017/08/14.
//
//

#include "ofxNoise.h"

ofxNoise::ofxNoise() {
  noise = ofRandom(1000);
  step = 0;
  min = 0;
  max = 0;
}

void ofxNoise::setup(float _step, float _max) {
  step = _step;
  min = 0;
  max = _max;
}

void ofxNoise::setup(float _step, float _min, float _max) {
  step = _step;
  min = _min;
  max = _max;
}

void ofxNoise::update() {
  noise += step;
}

void ofxNoise::setSpeed(float _step) {
  step = _step;
}

void ofxNoise::setRange(float _min, float _max) {
  min = _min;
  max = _max;
}

float ofxNoise::getNoise() {
  float n = ofMap(ofNoise(noise), 0, 1, min, max);
  
  return n;
}
//--------------------------------------------------------------
