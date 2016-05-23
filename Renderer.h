#pragma once

#include "ofMain.h"
// Created by Aart Odding, May 2016.
// This is a program that can be used to generate PNG images out of the dataset provided by the Shuttle radar Topogrpahy Mission
// http://srtm.csi.cgiar.org/SELECTION/inputCoord.asp
// build on Open Frameworks 0.9.3


class Renderer {

public:

	Renderer();
	void render(int thresh);

private:

	void switchSide();
	void newData(string data);
	void readLine(ifstream& file);
	ofColor constantColorAt(const int h);
	ofColor mappedColorAt(const int h);
	ofColor manualColorAt(const int h);

	int threshold;
	int values_calculated;

	ofPixels relief_image;
	ifstream left_side, right_side;
	ifstream* current_side;

	ofImage alphaMask;

};