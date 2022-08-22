# OSC2DMX
OSC to DMX bridge app with support for Serial (Enttec DMX USB Pro), Art-Net and simulator software.

This is an application built on openFramweworks & addons.

## Compiling

Currently only MacOs binaries are provided.

Compile for other platforms with openFrameworks version > 0.11 and additional addons: ofxArtnet, ofxDmx, ofxDropdown.

## Using 3DView simulator software

3DView is a lighting simulator included in the free theLighingController by SweetLight.

- start 3DView
- run `lsof | grep 3DView` to get the UDP port number
- enter port number in OSC2DMX

## Todo
- add sACN (streaming ACN) / E131 support using https://github.com/PlaymodesStudio/ofxE131Client
