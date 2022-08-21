#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    
    artnet.setup("127.0.0.1");
    
    gui.setup(); // most of the time you don't need a name
    
    groupOSC.setName("OSC");
    groupOSC.add(oscPort.set("port", 7770));
    groupOSC.add(oscPath.set("path", "/dmx/universe"));
    gui.add(groupOSC);
    
    groupArtnet.setName("artnet");
    groupArtnet.add(useArtnet.set("enabled", false));
    groupArtnet.add(targetArtnet.set("target", "127.0.0.1"));
    groupArtnet.add(portArtnet.set("port", 6465));
    gui.add(groupArtnet);
    
    groupDMX.setName("DMX");
    groupDMX.add(useDMX.set("enabled", false));
    gui.add(groupDMX);
    
    group3DView.setName("SL3DView");
    group3DView.add(use3DView.set("enabled", false));
    group3DView.add(port3DView.set("port", ""));
    gui.add(group3DView);
    
    gui.loadFromFile("settings.xml");
    
    oscReceiver.setup(oscPort);
}

//--------------------------------------------------------------
void ofApp::update(){
    if (oscReceiver.getPort() != oscPort) {
        oscReceiver.setup(oscPort);
    }
    
    int myPort = ofToInt(port3DView.get());
    if (use3DView && myPort > 1023) {
        udp3DView.Close();
        udp3DView.Create();
        udp3DView.Connect("127.0.0.1", myPort);
    }

    while(oscReceiver.hasWaitingMessages()){
        ofxOscMessage m;
        oscReceiver.getNextMessage(m);
        if (m.getAddress().substr(0, oscPath.get().length()) == oscPath.get()){
            ofBuffer data = m.getArgAsBlob(0);
            forwardData(data);
        }
    }
}

void ofApp::forwardData(const ofBuffer &data) {
    if (useArtnet) {
        unsigned char* pixels = const_cast<unsigned char*>(reinterpret_cast<const unsigned char*>(data.getData()));
        ofPixels pix;
        pix.setFromPixels(pixels, data.size(), 1, 1);
        artnet.sendArtnet(pix);
    }
    
    if (useDMX) {
        // todo: forward to serial
    }
    
    if (use3DView) {
        std::vector<unsigned char> udpBuf;
        
        int headSize = HEAD_3DVIEW.length();
        int dataSize = data.size();
        udpBuf.resize(headSize + dataSize + 1);
        
        for (int i = 0; i < headSize; i++) {
            udpBuf[i] = HEAD_3DVIEW[i];
        }
        udpBuf[headSize] = 0;

        memcpy(&udpBuf[headSize+1], data.getData(), dataSize);
        
        udp3DView.Send((const char *)udpBuf.data(), udpBuf.size());
    }
}
//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    
    gui.draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case 's':
            gui.saveToFile("settings.xml");
            ofLog() << "saved settings.xml";
            break;
        case 'l':
            gui.loadFromFile("settings.xml");
            break;
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
