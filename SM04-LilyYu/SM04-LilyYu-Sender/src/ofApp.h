#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxNDI.h"
#include "ofxOsc.h"
#include "ofxBox2d.h"

class ofApp : public ofBaseApp{

	public:
		void setup() override;
		void update() override;
		void draw() override;
		void exit() override;
    
        
        std::string sendAddr;
        int sendPort;

        ofxOscSender sender;
    
        // NDI receiver for pixels
        ofxNDIreceiver ndiReceiver;
        ofTexture ndiTexture;
    
        ofxBox2d box2d;
        vector <shared_ptr<ofxBox2dCircle>> circles;
    
        ofxButton uiClearCircles;
    
        ofxPanel gui;

//		void keyPressed(int key) override;
//		void keyReleased(int key) override;
//		void mouseMoved(int x, int y ) override;
//		void mouseDragged(int x, int y, int button) override;
		void mousePressed(int x, int y, int button) override;
//		void mouseReleased(int x, int y, int button) override;
//		void mouseScrolled(int x, int y, float scrollX, float scrollY) override;
//		void mouseEntered(int x, int y) override;
//		void mouseExited(int x, int y) override;
//		void windowResized(int w, int h) override;
//		void dragEvent(ofDragInfo dragInfo) override;
//		void gotMessage(ofMessage msg) override;
		
};
