#include "MandelBrot/HSV.hpp"
#include "MandelBrot/RGB.hpp"
#include "MandelBrot/ColourSpace.hpp"
#include <cmath>

HSV::HSV() : h(1), s(1), v(1) {};
HSV::HSV(float hue, float saturation, float value) 
	: h(hue), s(saturation), v(value){}

HSV::HSV(const HSV& other) 
	: h(other.h), s(other.s), v(other.v){}

HSV HSV::operator=(const HSV& other)
{ 
	this->h = other.h;
	this->s = other.s;
	this->v = other.v;

	return *this;
}

void HSV::interpolate(
	ColourSpacePtr& col1,
	ColourSpacePtr& col2,
	ColourSpacePtr& result, const float delta)
{
	//just make sure we are in HSV Space
	col1->toHSV(*col1.get());
	col2->toHSV(*col2.get());
	result->toHSV(*result.get());
	
	float hue1 = col1->getR();
	float hue2 = col2->getR();

	// edge case handling
	if (hue2 <= hue1) {
		hue2 += 360;
	}

	//do the actual interpolation
	float hue = hue1 + (hue2 - hue1) * delta;
	hue = (int) hue % 360;
	float sat = col1->getG() + (col2->getG() - col1->getG()) * delta;
	float val = col1->getB() + (col2->getB() - col1->getB()) * delta;

	result->setR(hue); result->setG(sat); result->setB(val);
}

// source: https://www.cs.rit.edu/~ncs/color/t_convert.html
// transforms HSV to RGB space
void HSV::toRGB(ColourSpace& result)
{
	int i;
	float f, p, q, t;

	float h = this->getH();
	float s = this->getS();
	float v = this->getV();

	if (s == 0) {
		// achromatic (gray)
		result.setR(this->getV() * 255);
		result.setG(this->getV() * 255);
		result.setB(this->getV() * 255);
		return;
	}

	h /= 60;
	i = floor(h);
	f = h - i;
	p = v * (1 - s);
	q = v * (1 - s * f);
	t = v * (1 - s * (1 - f));

	switch (i) {
		case 0:
			result.setR(std::round(v * 255));
			result.setG(std::round(t * 255));
			result.setB(std::round(p * 255));
			break;
		case 1:
			result.setR(std::round(q * 255));
			result.setG(std::round(v * 255));
			result.setB(std::round(p * 255));
			break;
		case 2:
			result.setR(std::round(p * 255));
			result.setG(std::round(v * 255));
			result.setB(std::round(t * 255));
			break;
		case 3:
			result.setR(std::round(p * 255));
			result.setG(std::round(q * 255));
			result.setB(std::round(v * 255));
			break;
		case 4:
			result.setR(std::round(t * 255));
			result.setG(std::round(p * 255));
			result.setB(std::round(v * 255));
			break;
		default:		
			result.setR(std::round(v * 255));
			result.setG(std::round(p * 255));
			result.setB(std::round(q * 255));
			break;
	}
}

void HSV::toHSV(ColourSpace& result) { result = *this; }