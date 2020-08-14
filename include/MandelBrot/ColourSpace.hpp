/*
This abstract class is the interface for different colour spaces. 
All colour spaces, need to inherit from this class in order to provide 
compatibility with the fractal generation. 
*/

#ifndef ColourSpace_HPP
#define ColourSpace_HPP

#include <memory>
#include <iostream>

class ColourSpace
{
public:
	using ColourSpacePtr = std::unique_ptr<ColourSpace>;

	ColourSpace() = default;
	virtual ~ColourSpace() = default;
	ColourSpace& operator=(const ColourSpace&) = default;
	ColourSpace(const ColourSpace&) = default;
	
	// first two colours are colours which will be used for interpolation
	// last colour parameter will get the result written
	virtual void interpolate(ColourSpacePtr&, ColourSpacePtr&, ColourSpacePtr&, const float) = 0;
	virtual void toRGB(ColourSpace&) = 0;
	virtual void toHSV(ColourSpace&) = 0;

	virtual float getR() const = 0;
	virtual float getG() const = 0;
	virtual float getB() const = 0;

	virtual void setR(const float) = 0;
	virtual void setG(const float) = 0;
	virtual void setB(const float) = 0;

};

#endif