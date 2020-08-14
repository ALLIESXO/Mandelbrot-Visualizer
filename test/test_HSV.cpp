#include <gtest/gtest.h>
#include "MandelBrot/HSV.hpp"
#include "MandelBrot/RGB.hpp"


TEST(HSV, testDefaultValues) {
	HSV defaultHSV = HSV();

	EXPECT_EQ(defaultHSV.getH(), 1.0);
	EXPECT_EQ(defaultHSV.getS(), 1.0);
	EXPECT_EQ(defaultHSV.getV(), 1.0);
}

TEST(HSV, testToHSV) {
	HSV defaultHSV = HSV();
	defaultHSV.toHSV(defaultHSV);

	EXPECT_EQ(defaultHSV.getH(), 1.0);
	EXPECT_EQ(defaultHSV.getS(), 1.0);
	EXPECT_EQ(defaultHSV.getV(), 1.0);
}

// Test if HSV can be converted to RGB
TEST(HSV, testToRGB) {

	HSV whiteHSV = HSV(0.0,0.0,1.0);
	RGB result = RGB(0, 0, 0);
	whiteHSV.toRGB(result);

	EXPECT_EQ(result.getR(), 255);
	EXPECT_EQ(result.getG(), 255);
	EXPECT_EQ(result.getB(), 255);

}

TEST(HSV, testInterpolation) {

	std::unique_ptr<ColourSpace> col1 (new HSV(0.0, 0.0, 0.0));
	std::unique_ptr<ColourSpace> col2 (new HSV(0.0, 1.0, 1.0));// red with too much brightness (looks white)
	std::unique_ptr<ColourSpace> result (new HSV());

	result->interpolate(col1, col2, result, 0.5);
	
	EXPECT_EQ(result->getR(), 180.0);
	EXPECT_EQ(result->getG(), 0.5);
	EXPECT_EQ(result->getB(), 0.5);

}