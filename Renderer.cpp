// Created by Aart Odding, May 2016.
// This is a program that can be used to generate PNG images out of the dataset provided by the Shuttle radar Topogrpahy Mission
// http://srtm.csi.cgiar.org/SELECTION/inputCoord.asp
// build on Open Frameworks 0.9.3


#include "Renderer.h"
#include "constants.h"

using namespace constants;

Renderer::Renderer() {
	alphaMask.load("maskFinal.png");
}


void Renderer::render(int thresh) {
	threshold = thresh;
	values_calculated = 0;

	left_side.open("/users/aart_/Projects/Open Frameworks/reliefRenderer/leftHalf.txt");
	right_side.open("/users/aart_/Projects/Open Frameworks/reliefRenderer/rightHalf.txt");

	if (left_side.fail() || right_side.fail()) ::exit(1);		// check if both files loaded correctly
	current_side = &left_side;

	relief_image.allocate(HORIZONTAL_PIXELS, VERTICAL_PIXELS, OF_IMAGE_COLOR_ALPHA);

	// so far only preparing and resetting, creating image starts here
	while (!right_side.eof()) {
		readLine(*current_side);
		switchSide();
	}

	// after the getting pixel data ready save image
	//relief_image.update();
	string image_name = "relief" + ofToString(threshold) + ".png";
	ofSaveImage(relief_image, image_name);
	cout << endl << image_name + " finished" << endl << endl;

	// finally close file streams
	left_side.close();
	right_side.close();
}


void Renderer::newData(string data) {

	int data_as_int = std::stoi(data);

	int x = values_calculated % 12'002;
	int y = values_calculated / 12'002;

	if (y >= NORTH_START && y <= SOUTH_STOP) {
		if (x >= WEST_START && x <= EAST_STOP) {

			int rX = x - WEST_START;
			int rY = y - NORTH_START;

			if (alphaMask.getColor(rX, rY) == ofColor(0) && data_as_int > threshold) {  // if value on mask image is white
				relief_image.setColor(rX, rY, manualColorAt(data_as_int));				// change function call depending on what color scheme you want
			}
			else {
				relief_image.setColor(rX, rY, ofColor(255, 255, 255, 0));		// alpha was 0
			}
		}
	}
	++values_calculated;
	if (values_calculated % 1'000'000 == 0) cout << values_calculated / 1'000'000 << " ";

}


void Renderer::readLine(ifstream& file) {
	int value = file.get();

	if (value == EOF) {
		return;
	}
	else {
		string data_buffer = "";
		while (value != 10) {
			if (value == 32) {
				newData(data_buffer);
				data_buffer = "";
			}
			else {
				data_buffer += value;
			}
			value = file.get();
		}
	}
}


void Renderer::switchSide() {
	if (current_side == &left_side) current_side = &right_side;
	else current_side = &left_side;
}

// COLOR MAPPING FUNCTIONS 
// to select which one should be used for the renderer the function call in newData() function should be changed.

ofColor Renderer::constantColorAt(const int h) {
	int brightness = 255 - (h + 10);			// this was 10
	if (brightness > 255) brightness = 255;
	else if (brightness < 0) brightness = 0;

	return ofColor(154, 205, 50, 255);
}


ofColor Renderer::mappedColorAt(const int h) {
	int height = h + 10;

	if (height < 0) height = 0;
	else if (height > 300) height = 300;

	int inverted_height = abs(height - 300);
	inverted_height = pow(inverted_height, 4);

	int red = ofMap(inverted_height, 0, pow(300, 4), 255, 0);
	int green = ofMap(inverted_height, 0, pow(300, 4), 195, 153);

	return ofColor(red, green, 0, 255);
}


ofColor Renderer::manualColorAt(const int h) {
	const int n_values = 36;
	int thresholds[n_values] = { 
		-6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
		12, 14, 16, 18, 20, 25, 30, 35, 40, 45, 50,
		60, 70, 80, 90, 100, 110, 120, 130 
	};
	int index = 0;

	while (h > thresholds[index]) {
		++index;
	}

	int red = ofMap(index, 0, n_values, 30, 200); // was 255
	int green = ofMap(index, 0, n_values, 143, 161); // both 30 reduced

	return ofColor(red, green, 50, 255);
}