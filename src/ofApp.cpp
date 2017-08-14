#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofBackground(0);
  ofSetFrameRate(60);
  
  nscale.setup(0.01, 0.005);
  nx.setup(0.01, -0.0001, 0.0001);
  ny.setup(0.01, -0.0001, 0.0001);
  cmax.setup(0.01, 255);
  cmin.setup(0.01, 255);
  nys.setup(0.01, 1);
  
//  mesh.setMode(OF_PRIMITIVE_TRIANGLES);
      mesh.setMode(OF_PRIMITIVE_LINES);
//      mesh.setMode(OF_PRIMITIVE_POINTS);
  
  step = 5;
  width = ofGetWidth() / (float)step + 2;
  height = ofGetHeight() / (float)step + 2;
  
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      ofVec3f v = ofVec3f(x*step, y*step, 0);
      ofColor c = ofColor::fromHsb(ofNoise(x*0.01, y*0.01)*255, 255, 255);
      
      mesh.addVertex(v);
      mesh.addColor(c);
      
    }
  }
  
  for (int y = 0; y<height-1; y++){
    for (int x=0; x<width-1; x++){
      mesh.addIndex(x+y*width);				// 0
      mesh.addIndex((x+1)+y*width);			// 1
      mesh.addIndex(x+(y+1)*width);			// 10
      
      mesh.addIndex((x+1)+y*width);			// 1
      mesh.addIndex((x+1)+(y+1)*width);		// 11
      mesh.addIndex(x+(y+1)*width);			// 10
    }
  }
  
  gui.setup();
  gui.add(scale.set("scale", ofVec2f(0.01, 0.01), ofVec2f(0, 0), ofVec2f(0.1, 0.1)));
  gui.add(px.set("x", ofVec2f(0.001, 0.0001), ofVec2f(0, 0), ofVec2f(0.1, 0.0005)));
  gui.add(py.set("y", ofVec2f(0.001, 0.0001), ofVec2f(0, 0), ofVec2f(0.1, 0.0005)));
  gui.add(max.set("colorRange", ofVec2f(0.01, 255), ofVec2f(0, 0), ofVec2f(0.1, 255)));
  gui.add(min.set("colorPos", ofVec2f(0.01, 255), ofVec2f(0, 0), ofVec2f(0.1, 255)));
  gui.add(addy.set("add y", 0.5, 0, 1));
  gui.add(addh.set("hue pos", 0, 0, 255));
  gui.add(useBrightness.set("b", false));
  gui.add(saturation.set("saturation", 255, 0, 255));
  gui.add(zheight.set("z height", 1, 0, 10));


  
  noisex0 = 0;
  
  cam.setScale(1,-1,1);
  
  guiDraw = true;
}
//--------------------------------------------------------------
void ofApp::update(){
  noiseUpdate();
  
  for (int y = 0; y < height; y++) {
    noisex = noisex0;
    for (int x = 0; x < width; x++) {
      int h = ofMap(ofNoise(x*nscale.getNoise() + noisex, y*nscale.getNoise() + noisey), 0, 1, cmin.getNoise(), cmin.getNoise()+cmax.getNoise()) + y*addy + addh;
      
      int b = ofMap(ofNoise(x*nscale.getNoise() + noisex, y*nscale.getNoise() + noisey), 0, 1, 0, 255);
      
      while (h > 255) {
        h -= 255;
      }
      
      ofVec3f v = ofVec3f(x*step, y*step, b*zheight);

      
      ofColor c;
      if(useBrightness) {
        c = ofColor::fromHsb(h, saturation, b);
      } else {
        c = ofColor::fromHsb(h, saturation, 255);
      }

//      mesh.setVertex(x + y * width, v);
      mesh.setColor(x + y * width, c);
      noisex += nx.getNoise();
    }
    noisey += ny.getNoise();
    noisex0 += nx.getNoise();
  }
}

void ofApp::noiseUpdate() {
  nscale.update();
  nscale.setSpeed(scale->x);
  nscale.setRange(0, scale->y);

  nx.update();
  nx.setSpeed(px->x);
  nx.setRange(-px->y, px->y);

  ny.update();
  ny.setSpeed(py->x);
  ny.setRange(-py->y, py->y);

  cmax.update();
  cmax.setSpeed(max->x);
  cmax.setRange(0, max->y);

  cmin.update();
  cmin.setSpeed(min->x);
  cmin.setRange(0, min->y);
}

//--------------------------------------------------------------
void ofApp::draw(){
  ofEnableDepthTest();
  cam.begin();
  
  ofSetColor(255, 255, 255);
  mesh.draw();
  
  cam.end();
  
//  ofSetColor(255);
//  ofDrawBitmapString(ofToString(nscale.getNoise()), 20, 20);
//  ofDrawBitmapString(ofToString(nx.getNoise(), 8), 20, 50);
//  ofDrawBitmapString(ofToString(ny.getNoise(), 8), 20, 80);
//  ofDrawBitmapString(ofToString(cmax.getNoise()), 20, 110);
//  ofDrawBitmapString(ofToString(cmin.getNoise()), 20, 140);
  
  if (guiDraw) {
    ofDisableDepthTest();
    ofSetColor(255, 255, 255);
    gui.draw();
  }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  if (key == 'g') {
    guiDraw = !guiDraw;
  }
  if (key == '0') {
    mesh.setMode(OF_PRIMITIVE_LINES);
  }
  if (key == '1') {
    mesh.setMode(OF_PRIMITIVE_POINTS);
  }
  if (key == '2') {
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
  }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
