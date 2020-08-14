#include <gtest/gtest.h>
#include "MandelBrot/HSV.hpp"
#include "MandelBrot/RGB.hpp"


TEST(RGB, testDefaultValues) {
	RGB defaultRGB = RGB();

	EXPECT_EQ(defaultRGB.getR(), 255);
	EXPECT_EQ(defaultRGB.getG(), 255);
	EXPECT_EQ(defaultRGB.getB(), 255);
}

// Test if RGB can be converted to HSV
TEST(RGB, testToHSV) {

	RGB whiteRGB = RGB();
	HSV result = HSV();
	whiteRGB.toHSV(result);

	EXPECT_EQ(result.getH(), 0);
	EXPECT_EQ(result.getS(), 0);
	EXPECT_EQ(result.getV(), 1);
}
TEST(RGB, testToRGB) {

	RGB defaultRGB = RGB();
	defaultRGB.toRGB(defaultRGB);

	EXPECT_EQ(defaultRGB.getR(), 255);
	EXPECT_EQ(defaultRGB.getG(), 255);
	EXPECT_EQ(defaultRGB.getB(), 255);
}

TEST(RGB, testInterpolation) {

	std::unique_ptr<ColourSpace> col1(new RGB(0, 100, 200));
	std::unique_ptr<ColourSpace> col2(new RGB(100, 200, 250));
	std::unique_ptr<ColourSpace> result(new RGB());
	result->interpolate(col1, col2, result, 0.5);

	EXPECT_EQ(result->getR(), 50);
	EXPECT_EQ(result->getG(), 150);
	EXPECT_EQ(result->getB(), 225);
}