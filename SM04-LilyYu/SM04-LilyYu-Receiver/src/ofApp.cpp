#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowShape(640, 480);
    
    nearThreshold.set("Near Threshold", 0.01f, 0.0f, 0.1f);
    farThreshold.set("Far Threshold", 0.02f, 0.0f, 0.1f);
    
    gui.setup();
    gui.add(uiClearCircles.setup("clear circles"));
    gui.add(nearThreshold);
    gui.add(farThreshold);
    
    kinect.setRegistration(true);
    kinect.init();
    kinect.open();
    
    color.allocate(kinect.getWidth(), kinect.getHeight());
    
    // Set up the OSC receiver.
    recvPort = 3030;
    receiver.setup(recvPort);

    // Set up NDI senders.
//    ndiSender.CreateSender("NDI Sender", kinect.getWidth(), kinect.getHeight());
    
    box2d.init();
    box2d.setGravity(0, 30);
    box2d.createGround();
    box2d.createBounds(ofRectangle(0, 0, kinect.getWidth(), kinect.getHeight()));
}

//--------------------------------------------------------------
void ofApp::update(){
    box2d.update();
    kinect.update();
    
    if (kinect.isFrameNew()){
        color.setFromPixels(kinect.getPixels());
        
        const ofFloatPixels& rawDepthPix = kinect.getRawDepthPixels();
        
        ofFloatPixels thresholdNear, thresholdFar, thresholdResult;
        
        ofxCv::threshold(rawDepthPix, thresholdNear, nearThreshold);
        ofxCv::threshold(rawDepthPix, thresholdFar, farThreshold, true);
        ofxCv::bitwise_and(thresholdNear, thresholdFar, thresholdResult);
        
        thresholdImg.setFromPixels(thresholdResult);

        int minimum = thresholdImg.getWidth() * thresholdImg.getHeight() * 0.05;
        int maximum = thresholdImg.getWidth() * thresholdImg.getHeight() * 0.8;
        
        contour.findContours(thresholdImg, minimum, maximum, 1, false);
        
        // use NDI to send pixels
//        ndiSender.SendImage(thresholdResult);
    }
    
    if (uiClearCircles){
        circles.clear();
    }
    
    while (receiver.hasWaitingMessages())
    {
        // Get the next message.
        ofxOscMessage msg;
        receiver.getNextMessage(msg);

        if (msg.getAddress() == "/cursor/move")
        {
            cursorX = msg.getArgAsInt(0);
            cursorY = msg.getArgAsInt(1);
            
            auto circle = make_shared<ofxBox2dCircle>();
            circle->setPhysics(3.0, 0.5, 0.1);
            circle->setup(box2d.getWorld(), cursorX, cursorY, 32);
            circles.push_back(circle);
        }
        else
        {
            ofLogWarning(__FUNCTION__) << "Unrecognized message " << msg.getAddress();
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    
    color.draw(0, 0);
    
    if (!contour.blobs.empty()){
      createContourEdge(ofPolyline(contour.blobs.at(0).pts));
      contourEdge->draw();
    }
    
    for (auto circle:circles){
      circle->draw();
    }
    
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::exit(){
    kinect.setCameraTiltAngle(0);
    kinect.close();
}

//--------------------------------------------------------------
void ofApp::createContourEdge(ofPolyline polyline){
  delete contourEdge;
  contourEdge = new ofxBox2dEdge();
  contourEdge->addVertexes(polyline);
  contourEdge->create(box2d.getWorld());
}
