// Created by Aart Odding, May 2016.
// This is a program that can be used to generate PNG images out of the dataset provided by the Shuttle radar Topogrpahy Mission
// http://srtm.csi.cgiar.org/SELECTION/inputCoord.asp
// build on Open Frameworks 0.9.3

// FOR INSTRUCTIONS SEE "ofApp.cpp"


#include "ofMain.h"
#include "ofApp.h"

int main( ){
	ofSetupOpenGL(1024,768,OF_WINDOW);
	ofRunApp(new ofApp());
}
