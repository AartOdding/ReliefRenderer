// Created by Aart Odding, May 2016.
// This is a program that can be used to generate PNG images out of the dataset provided by the Shuttle radar Topogrpahy Mission
// http://srtm.csi.cgiar.org/SELECTION/inputCoord.asp
// build on Open Frameworks 0.9.3


#pragma once

namespace constants {

	const int NORTH_START = 1700;
	const int WEST_START = 4000;
	const int SOUTH_STOP = 5119;
	const int EAST_STOP = 8699;

	const int HORIZONTAL_PIXELS = EAST_STOP - WEST_START + 1;
	const int VERTICAL_PIXELS = SOUTH_STOP - NORTH_START + 1;

	const int TOTAL_PIXELS = HORIZONTAL_PIXELS * VERTICAL_PIXELS;

}