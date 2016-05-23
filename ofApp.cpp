// Created by Aart Odding, May 2016.
// This is a program that can be used to generate PNG images out of the dataset provided by the Shuttle radar Topogrpahy Mission
// http://srtm.csi.cgiar.org/SELECTION/inputCoord.asp
// build on Open Frameworks 0.9.3

// by placing integer values in the thresholds vector, you can tell the program for which sea levels, it shoudl calculate the view of the netherlands.

#include "ofApp.h"
#include "Renderer.h"


void ofApp::setup(){

	Renderer image_renderer;
	vector <int> thresholds = {				// put all the sea levels that you want to calculate in here.
		-9, -10
	};

	for (int t = 0; t < thresholds.size(); t++) {
		image_renderer.render(thresholds[t]);
	}

	cout << "finished" << endl;

	system("pause");
	::exit(0);
}

/*
{-6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
12, 14, 16, 18, 20, 25, 30, 35, 40, 45, 50,
60, 70, 80, 90, 100, 110, 120, 130 };
*/