#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    
    artnet.setup(artnetIp, artnetPort);
    
    gui.setup(); // most of the time you don't need a name
    
    groupOSC.setName("OSC");
    groupOSC.add(oscPort.set("port", 7770));
    groupOSC.add(oscPath.set("path", "/dmx/universe"));
    gui.add(groupOSC);
    
    groupArtnet.setName("artnet");
    groupArtnet.add(useArtnet.set("enabled", false));
    groupArtnet.add(targetArtnet.set("target", artnetIp));
    groupArtnet.add(portArtnet.set("port", artnetPort));
    gui.add(groupArtnet);
    
    dmxPort.setName("port");
    serialDropdown =  make_unique<ofxDropdown>(dmxPort);
    vector<ofSerialDeviceInfo> devices = serial.getDeviceList();
    for(int i = 0; i < devices.size(); i++){
        serialDropdown->add(devices[i].getDevicePath());
    }
    
    groupDMX.setName("Enttec DMX USB Pro");
    groupDMX.add(useDMX.set("enabled", false));
    gui.add(groupDMX);
    ofxBaseGui* group = gui.getControl(gui.getNumControls()-1);
    dynamic_cast<ofxGuiGroup*>(group)->add(serialDropdown.get());
    
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
    
    if (artnetIp != targetArtnet.get() || artnetPort != portArtnet.get()) {
        artnetIp = targetArtnet.get();
        artnetPort = portArtnet.get();
        artnet.setup(artnetIp, artnetPort);
    }
    
    if (connectedDmxPort != dmxPort.get() && invalidDmxPort != dmxPort.get()) {
        if (dmx.connect(dmxPort.get(), 512)) {
            connectedDmxPort = dmxPort.get();
            dmxPort.setName("port - connected");
        }
        else {
            invalidDmxPort = dmxPort.get();
            dmxPort.setName("port - NOT connected");
        }
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
        unsigned char* udata = const_cast<unsigned char*>(reinterpret_cast<const unsigned char*>(data.getData()));
        ofPixels pix;
        pix.setFromPixels(udata, data.size(), 1, 1);
        artnet.sendArtnet(pix);
    }
    
    if (useDMX && dmx.isConnected()) {
        unsigned char* udata = const_cast<unsigned char*>(reinterpret_cast<const unsigned char*>(data.getData()));
        // quickfix: add to ofxDmx.h
//        void setLevels(unsigned char* value, int len) {
//            levels.assign(value, value + len);
//        }
//        void setLevels(unsigned char* value) {
//            setLevels(value, levels.size());
//        }
//        void setLevels2(unsigned char* value, int len) {
//            levels2.assign(value, value + len);
//        }
//        void setLevels2(unsigned char* value) {
//            setLevels2(value, levels2.size());
//        }
        dmx.setLevels(udata);
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
