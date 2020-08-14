#include <opencv2/opencv.hpp>
#include "MandelBrot/Settings.hpp"
#include "MandelBrot/Fractal.hpp"

using namespace cv;
using FractalType = Fractal<long double>;
using namespace std::literals;

int main(int argc, char const *argv[]) {

	// initialize Settings with parameters 
	Settings& settings(Settings::getInstance());
	settings.initialize(argc, argv);

	Mat image;
	//create image based on parameters 
	if (settings.parameters.find("-BurningShip"s)->second.first != 0) {
		image = FractalType::createImage(FractalType::BurningShip, settings);
	}
	else {
		image = FractalType::createImage(FractalType::Mandelbrot, settings);
	}

	imshow("Fractal-Visualizer", image);
	waitKey(0);

	return 0;
}