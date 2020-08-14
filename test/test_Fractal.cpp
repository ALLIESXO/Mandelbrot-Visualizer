#include <gtest/gtest.h>
#include "MandelBrot/Fractal.hpp"
#include "opencv2/opencv.hpp"

using namespace std::complex_literals;
using FractalType = Fractal<long double>;

// Test if the fractal functions can be used for abitrary type (float ,...) 
TEST(Fractals, testMandelbrotValue) {

	// double 
	std::complex<double> z = 0.0 + 0.0i;
	std::complex<double> c = 0.5 + 0.5i;
	auto res = Fractal<double>::Mandelbrot(z, c);
	EXPECT_EQ(res, (0.5 + 0.5i));

	// float 
	std::complex<float> z2 = 0.0 + 0.0i;
	std::complex<float> c2 = 0.5 + 0.5i;
	auto res2 = Fractal<float>::Mandelbrot(z2, c2);
	EXPECT_EQ(res2, std::complex<float> (0.5 + 0.5i));

	// Reminder: never program C++ applications on windows. -- wasted hours to get boost library up and running without success.
	// with boost it would be possible to test if our fractal can be successfully calculated using mpfr (boost::multiprecision) 
	// In theory it should work just fine if it is a cv classified floating point data type.
}


TEST(Fractals, testBurningShipValue) {

	// double 
	std::complex<double> z = 0.0 + 0.0i;
	std::complex<double> c = 0.5 + 0.5i;
	auto res = Fractal<double>::BurningShip(z, c);
	EXPECT_EQ(res, (0.5 + 0.5i));

	// float 
	std::complex<float> z2 = 0.0 + 0.0i;
	std::complex<float> c2 = 0.5 + 0.5i;
	auto res2 = Fractal<float>::BurningShip(z2, c2);
	EXPECT_EQ(res2, std::complex<float>(0.5 + 0.5i));
}

//TODO: uncomment for release
/*
TEST(Fractals, testFunctionPass) {
	Settings& settings(Settings::getInstance());
	int height = (int) settings.getHeight() / 2;
	int width = (int)settings.getWidth() / 2;

	auto image1 = FractalType::createImage(FractalType::Mandelbrot, settings);
	auto image2 = FractalType::createImage(FractalType::BurningShip, settings);

	auto vec1 = image1.at<cv::Vec3b>(height, width);
	auto vec2 = image2.at<cv::Vec3b>(height, width);

	// white is not a possible colour anywhere in the image
	EXPECT_FALSE(vec1[2] == 255);
	EXPECT_FALSE(vec2[2] == 255);
}*/
