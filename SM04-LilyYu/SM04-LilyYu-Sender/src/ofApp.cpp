#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowShape(640, 480);
    
    gui.setup();
    gui.add(uiClearCircles.setup("clear circles"));
    
    // Set up the OSC sender.
    sendAddr = "localhost";
    sendPort = 3030;
    sender.setup(sendAddr, sendPort);
    
    // Set up the NDI receiver
//    ndiTexture.allocate(640, 480, GL_RGBA);
    
    
    box2d.init();
    box2d.setGravity(0, 30);
    box2d.createGround();
}

//--------------------------------------------------------------
void ofApp::update(){
    box2d.update();
    
//    ndiReceiver.ReceiveImage(ndiTexture);
    
    if (uiClearCircles){
        circles.clear();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    
//    ndiTexture.draw(0, 0);
    
    for (auto circle:circles){
      circle->draw();
    }
    
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::exit(){

}

////--------------------------------------------------------------
//void ofApp::keyPressed(int key){
//
//}
//
////--------------------------------------------------------------
//void ofApp::keyReleased(int key){
//
//}
//
////--------------------------------------------------------------
//void ofApp::mouseMoved(int x, int y ){
//
//}
//
////--------------------------------------------------------------
//void ofApp::mouseDragged(int x, int y, int button){
//
//}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    auto circle = make_shared<ofxBox2dCircle>();
    circle->setPhysics(3.0, 0.5, 0.1);
    circle->setup(box2d.getWorld(), x, y, 32);
    circles.push_back(circle);
    
    // send mouse positions
    ofxOscMessage msg;
    msg.setAddress("/cursor/move");
    msg.addIntArg(ofGetMouseX());
    msg.addIntArg(ofGetMouseY());

    sender.sendMessage(msg);}

////--------------------------------------------------------------
//void ofApp::mouseReleased(int x, int y, int button){
//
//}
//
////--------------------------------------------------------------
//void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){
//
//}
//
////--------------------------------------------------------------
//void ofApp::mouseEntered(int x, int y){
//
//}
//
////--------------------------------------------------------------
//void ofApp::mouseExited(int x, int y){
//
//}
//
////--------------------------------------------------------------
//void ofApp::windowResized(int w, int h){
//
//}
//
////--------------------------------------------------------------
//void ofApp::gotMessage(ofMessage msg){
//
//}
//
////--------------------------------------------------------------
//void ofApp::dragEvent(ofDragInfo dragInfo){
//
//}
