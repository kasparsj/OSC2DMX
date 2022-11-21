# OSC2DMX
OSC to DMX bridge app with support for Serial ([Enttec DMX USB Pro](https://www.enttec.com/product/lighting-communication-protocols/dmx512/dmx-usb-pro/)), Art-Net and simulator software.

This is an application built with [openFramweworks](https://openframeworks.cc/).

## Platforms

Currently only MacOs binaries are provided, but you can compile for other platforms with openFrameworks (>0.11) and additional addons: ofxArtnet, ofxDmx, ofxDropdown.

## Simulator software

### 3DView

3DView is a lighting simulator included in the free [theLighingController by SweetLight](https://sweetlight-controller.com/).

- start 3DView
- find 3DView listening port number (in Terminal run `lsof | grep 3DView` and look for UDP port number)
- enter port number in OSC2DMX

### BlendexDMX

[BlenderDMX](https://github.com/hugoaboud/BlenderDMX) is an open source Blender addon for DMX visualisation.

## Todo
- add sACN (streaming ACN) / E131 support using https://github.com/PlaymodesStudio/ofxE131Client
