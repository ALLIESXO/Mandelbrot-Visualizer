#include "MandelBrot/RGB.hpp"
#include "MandelBrot/HSV.hpp"
#include <algorithm>
#include <cmath>

RGB::RGB() : r(255), g(255), b(255) {}

RGB::RGB(float red, float green, float blue) 
	: r{ red }, g{ green }, b{ blue } {};

RGB::RGB(const RGB& other) {
	this->r = other.r;
	this->g = other.g;
	this->b = other.b;
}

RGB RGB::operator=(const RGB& other)
{
	this->r = other.r;
	this->g = other.g;
	this->b = other.b;

	return *this;
}

// Takes to RGB values and interpolates a colour between them.
// The third RGB object is modified to the resulted interpolated colour.
void RGB::interpolate(
	ColourSpacePtr& col1,
	ColourSpacePtr& col2,
	ColourSpacePtr& result, const float delta)
{	
	// make sure we are in RGB space
	col1->toRGB(*col1.get());
	col2->toRGB(*col2.get());
	result->toRGB(*result.get());
	
	// do the actual interpolation
	float red   = col1->getR() + (col2->getR() - col1->getR()) * delta;
	float green = col1->getG() + (col2->getG() - col1->getG()) * delta;
	float blue  = col1->getB() + (col2->getB() - col1->getB()) * delta;

	// set interpolated values
	result->setR(std::round(red));
	result->setG(std::round(green));
	result->setB(std::round(blue));
}

// transforms RGB to RGB space
void RGB::toRGB(ColourSpace& result) { result = *this; }

// transforms RGB to HSV space 
// source: https://www.cs.rit.edu/~ncs/color/t_convert.html
void RGB::toHSV(ColourSpace& result) {

	float h, s, v;
	
	// rgb needs to be in [0,1] range
	float r_n = this->getR() / 255;
	float g_n = this->getG() / 255;
	float b_n = this->getB() / 255;

	float min, max, delta;

	min = std::min(b_n, std::min(r_n, g_n));
	max = std::max(b_n, std::max(r_n, g_n));
	v = max;

	delta = max - min;

	if (max != 0) {
		s = delta / max;
	}
	else {
		// r = g = b = 0   therefore s = 0 and v is undefined (-1) 
		s = 0;
		h = -1; 
		return;
	}

	//avoid division by zero 
	if (delta == 0) {
		delta = 1.0;
	}

	if (r_n == max) {
		h = (g_n - b_n) / delta;
	}
	else if (g_n == max) {
		h = 2 + (b_n - r_n) / delta;
	} 
	else {
		h = 4 + (r_n - g_n) / delta;
	}

	h *= 60;

	if (h < 0) {
		h += 360;
	}

	result.setR(h);
	result.setG(s);
	result.setB(v);
}