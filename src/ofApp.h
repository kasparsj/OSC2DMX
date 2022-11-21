#pragma once

#include "ofMain.h"
#include "ofxArtnet.h"
#include "ofxGui.h"
#include "ofxOsc.h"
#include "ofxNetwork.h"
#include "ofxDmx.h"
#include "ofxDropdown.h"
#include "ofSerial.h"

class ofApp : public ofBaseApp{

    public:
        void setup();
        void update();
        void draw();

        void keyPressed(int key);
        void keyReleased(int key);
        void mouseMoved(int x, int y );
        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
        void mouseEntered(int x, int y);
        void mouseExited(int x, int y);
        void windowResized(int w, int h);
        void dragEvent(ofDragInfo dragInfo);
        void gotMessage(ofMessage msg);
    
    void forwardData(const ofBuffer &data);
    
    ofxPanel gui;
    ofParameterGroup groupOSC;
    ofParameterGroup groupArtnet;
    ofParameterGroup groupDMX;
    ofParameterGroup group3DView;
    
    ofParameter<unsigned short> oscPort;
    ofParameter<string> oscPath;

    ofParameter<bool> useArtnet;
    ofParameter<string> targetArtnet;
    ofParameter<unsigned short> portArtnet;
    
    ofSerial serial;
    unique_ptr<ofxDropdown> serialDropdown;
    
    ofParameter<bool> useDMX;
    ofParameter<string> dmxPort;
    string connectedDmxPort;
    string invalidDmxPort;
    
    ofParameter<bool> use3DView;
    ofParameter<string> port3DView;
    
    ofxOscReceiver oscReceiver;
    ofxUDPManager udp3DView;
    ofxArtnetSender artnet;
    string artnetIp = "127.0.0.1";
    int artnetPort = 6465;
    ofxDmx dmx;
    
    const std::string HEAD_3DVIEW = "DMX|";

};
