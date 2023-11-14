#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxNDI.h"
#include "ofxOsc.h"
#include "ofxBox2d.h"
#include "ofxKinect.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"


class ofApp : public ofBaseApp{

	public:
		void setup() override;
		void update() override;
		void draw() override;
		void exit() override;

        // Osc receiver for mouse positions
        int recvPort;
        ofxOscReceiver receiver;

        int cursorX;
        int cursorY;
    
        // NDI sender for pixels
        ofxNDIsender ndiSender;

        ofxBox2d box2d;
        vector <shared_ptr<ofxBox2dCircle>> circles;
        ofxBox2dEdge *contourEdge;

        ofxButton uiClearCircles;
    
        ofxKinect kinect;

        ofxPanel gui;
    
        ofxCvGrayscaleImage thresholdImg;
        ofxCvContourFinder contour;
        ofxCvColorImage color;

        ofParameter<float> nearThreshold;
        ofParameter<float> farThreshold;
    
        void createContourEdge(ofPolyline polyline);
		
};
