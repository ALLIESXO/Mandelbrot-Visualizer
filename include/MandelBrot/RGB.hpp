/* Class for saving RGB values. Also for interpolation and converting to other formats.*/

#ifndef RGB_HPP
#define RGB_HPP

#include "ColourSpace.hpp"
#include <utility>
#include <iostream>


class RGB : public ColourSpace
{
public:

	RGB();
	RGB(float r, float g, float b);
	RGB(const RGB& other);
	RGB operator=(const RGB& other);

	virtual void interpolate(
		ColourSpacePtr& col1,
		ColourSpacePtr& col2,
		ColourSpacePtr& result, const float) override final;

	virtual void toRGB(ColourSpace& result) override final;
	virtual void toHSV(ColourSpace& result) override final;

	virtual ~RGB() override = default;

	virtual float getR() const override final { return this->r; };
	virtual float getG() const override final { return this->g; };
	virtual float getB() const override final { return this->b; };

	virtual void setR(const float val) override final { r = val; }
	virtual void setG(const float val) override final { g = val; }
	virtual void setB(const float val) override final { b = val; }

private: 

	float r;
	float g;
	float b;
	
};

#endif


