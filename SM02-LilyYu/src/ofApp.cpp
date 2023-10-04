#include "ofApp.h"

using namespace ofxCv;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(120);
    finder.setup("haarcascade_frontalface_default.xml");
    finder.setPreset(ObjectFinder::Fast);
    
    cam.setup(1280, 720);
    ofSetWindowShape(1280, 720);
    
    gui.setup();
    gui.add(useGaussian.set("Use Gaussian", false));
    gui.add(radius.set("Radius", 50, 0, 100));
    gui.add(freezeCam.set("Freeze Camera", false));
}

//--------------------------------------------------------------
void ofApp::update(){
    if (!freezeCam) {
        cam.update();
        if(cam.isFrameNew()) {
            finder.update(cam);
    //        copy(finder, img);
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.draw(0, 0);
//    finder.draw();
    
//    if(roiImg.isAllocated()) {
//        roiImg.draw(0, 0);
//    }
    
    for (int i=0; i < finder.size(); i++) {
        ofRectangle object = finder.getObjectSmoothed(i);
//            inputImg.setROI(object);
        ofPixels& camPixels = cam.getPixels();
//        camPixels = cam.getPixels();
        ofImage roiImg;
//        roiImg.setFromPixels(cam.getPixels(), object.width, object.height, OF_IMAGE_COLOR);
        roiImg.setFromPixels(cam.getPixels());
        roiImg.crop(object.x, object.y, object.width, object.height);
        if (useGaussian) {
            GaussianBlur(roiImg, radius);
        } else {
            blur(roiImg, radius);
        }
        roiImg.update();
        ofPushMatrix();
        roiImg.setAnchorPoint(roiImg.getWidth()/2, roiImg.getHeight()/2);
        ofTranslate(object.x + object.width/2., object.y + object.height/2.);
//        ofTranslate(object.x, object.y);
        roiImg.draw(0, 0);
        ofPopMatrix();
    }
    
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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

