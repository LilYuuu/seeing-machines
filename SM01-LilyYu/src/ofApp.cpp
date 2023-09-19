#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    myImg.allocate(400, 300, OF_IMAGE_GRAYSCALE);

    ofPixels myPix = myImg.getPixels();
    for (int y = 0; y < myImg.getHeight(); y++)
    {
      for (int x = 0; x < myImg.getWidth(); x++)
      {
        if (ofRandomuf() < 0.5)
        {
          myPix.setColor(x, y, ofColor(0));
        }
        else
        {
          myPix.setColor(x, y, ofColor(255));
        }
      }
    }
    // getPixels() makes a copy of the pixels, so we need to
    // use setFromPixels to set the new values back on the image.
    myImg.setFromPixels(myPix);
    
    ofSetWindowShape(myImg.getWidth(), myImg.getHeight());
}

//--------------------------------------------------------------
void ofApp::update(){
    ofPixels myPix = myImg.getPixels();
    
    // press space key to pause and resume
    if (!paused) {
        for (int y = 0; y < myImg.getHeight(); y++) {
            for (int x = 0; x < myImg.getWidth(); x++) {
                // count neighbors alive
                int neighborsAlive = 0;
                for (int j=-1; j<2; j++) {
                    for (int i=-1; i<2; i++) {
                        // skip the center cell
                        if (i==0 && j==0) {
                            continue;
                        }
                        // edge cases
                        if (x+i < 0 || x+i > myImg.getWidth() || y+j < 0 || y+j > myImg.getHeight()) {
                            continue;
                        }

                        neighborsAlive += ifAlive(x+i, y+j);
                    }
                }
                // check if the center cell is alive
                if (ifAlive(x, y)) {
                    // isolation || overcrowding
                    if (neighborsAlive < 2 || neighborsAlive >= 4) {
                        myPix.setColor(x, y, ofColor(0));
                    }
                } else {
                    // reproduction
                    if (neighborsAlive == 3) {
                        
                        myPix.setColor(x, y, ofColor(255));
                    }
                }
            }
        }
        myImg.setFromPixels(myPix);
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    myImg.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == ' ') {
        paused = !paused;
    }
    
    if (key == 'r' || key == 'R') {
        resetAllCells();
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
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){

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

int ofApp::ifAlive(int x, int y) {
    ofColor thisColor = myImg.getColor(x, y);
    if (thisColor == ofColor(255)) {
        return 1;
    }
    return 0;
}

void ofApp::resetAllCells() {
    ofPixels myPix = myImg.getPixels();
    for (int y = 0; y < myImg.getHeight(); y++)
    {
      for (int x = 0; x < myImg.getWidth(); x++)
      {
        if (ofRandomuf() < 0.5)
        {
          myPix.setColor(x, y, ofColor(0));
        }
        else
        {
          myPix.setColor(x, y, ofColor(255));
        }
      }
    }
    // getPixels() makes a copy of the pixels, so we need to
    // use setFromPixels to set the new values back on the image.
    myImg.setFromPixels(myPix);
}
