#ifndef HSV_HPP
#define HSV_HPP

#include "ColourSpace.hpp"
#include "MandelBrot/RGB.hpp"
#include "MandelBrot/ColourSpace.hpp"
#include <iostream>

class HSV : public ColourSpace
{
public:
	HSV();
	HSV(float hue, float saturation, float value);
	HSV(const HSV& other);
	HSV operator=(const HSV& other);
	virtual ~HSV() override = default;

	virtual void interpolate (ColourSpacePtr& col1, ColourSpacePtr& col2, ColourSpacePtr& result, const float) override final;
	virtual void toRGB (ColourSpace& result) override final;
	virtual void toHSV(ColourSpace& result) override final;

	// wrapper functions
	const float getH() const { return getR(); }
	const float getS() const { return getG(); }
	const float getV() const { return getB(); }

	float setH(const float val) noexcept { setR(val); }
	float setS(const float val) noexcept { setG(val); }
	float setV(const float val) noexcept { setB(val); }

private:

	float h;
	float s;
	float v;

	virtual void setR(const float val) override final { h = val; }
	virtual void setG(const float val) override final { s = val; }
	virtual void setB(const float val) override final { v = val; }

	virtual float getR() const override final { return this->h; };
	virtual float getG() const override final { return this->s; };
	virtual float getB() const override final { return this->v; };

};
#endif