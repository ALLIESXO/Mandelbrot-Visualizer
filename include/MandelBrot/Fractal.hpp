/* All algorithm variants in order to calculate complex sets are given here. 
   Some set examples: Mandelbrot (main goal), Julia set, tricorn, burning ship fractal, ...
   In order to change the used algorithm - a parameter can be used. 
   The Fractal struct provides the main process to create an Image - only the type of function may be changed using templates.*/

#ifndef Fractal_HPP
#define Fractal_HPP
#include <opencv2/opencv.hpp>
#include <complex>
#include <type_traits>
#include "Settings.hpp"
#include <functional>
#include "MandelBrot/RGB.hpp"
#include "MandelBrot/HSV.hpp"

using namespace cv;

template<typename FloatType,
	typename std::enable_if<std::is_floating_point<FloatType>::value, bool>::type = true>
struct Fractal
{
	using complexFloat = std::complex<FloatType>;

	// Calculates mandelbrot algorithm (https://de.wikipedia.org/wiki/Mandelbrot-Menge)
	static complexFloat Mandelbrot(complexFloat z , complexFloat c) {
		return z * z + c;
	}

	// Calculates the burning ship algorithm (https://en.wikipedia.org/wiki/Burning_Ship_fractal)
	static complexFloat BurningShip(complexFloat z, complexFloat c) {
		z = complexFloat(abs(real(z)), 0) + complexFloat(0, abs(imag(z)));
		return z * z + c;
	}

	// createImage function calculates the complex sets based on the given function
	using FracFunction = std::function<complexFloat(complexFloat, complexFloat)>;
	static Mat createImage(FracFunction fracfunc, Settings& settings) {

		int height = settings.getHeight();
		int width = settings.getWidth();
		unsigned int maxIteration = settings.getMaxIterations();

		FloatType real = (FloatType) settings.getReal();
		FloatType imag = (FloatType) settings.getImag();
		FloatType diameter = (FloatType) settings.getHorizDiameter();
		float prog = settings.getColourProgression();
		std::unique_ptr<ColourSpace> interpolatedColour;

		if (settings.isRGBSpace()) {
			interpolatedColour.reset(new RGB());
		}
		else {
			interpolatedColour.reset(new HSV());
		}
		

		// Matrix coordinate (0,0) is at the upper left corner. 
		// we need to adjust the coordiante to the correct complex space 
		FloatType zoom = 1.0;

		FloatType minReal = (real - diameter * 0.5) / zoom;
		FloatType maxReal = (real + diameter * 0.5) / zoom;
		FloatType minImag = (-1.5 + imag) / zoom;
		FloatType maxImag = (minImag + (maxReal - minReal)* height/width) / zoom;

		auto amountColours = settings.getColours().size();

		Mat image (height, width, CV_8UC3, Scalar(0,0,0));
		
		// calculation of the fractal 
		for (int x = 0; x < width; x++) {
			FloatType realCoord = minReal + (maxReal - minReal) * x/(width-1);

			for (int y = 0; y < height; y++) {
				FloatType imagCoord = minImag + (maxImag - minImag) * y / (height - 1);

				complexFloat point(realCoord, imagCoord);

				std::complex<FloatType> z(0, 0);
				float iteration = 0;
				
				while (std::abs(z) < 128 && iteration <= maxIteration) { 
					z = fracfunc(z, point);
					iteration++;
				}
			
				if (iteration < maxIteration) { 

					// when applying the logarithm and the progressione
					// to the iteration variabl I encountered colouring issues

					//iteration = log(iteration) / log(maxIteration);
					//iteration *= prog;
					
					float log_zn = (std::log(std::abs(z))) / 2;
					float nu = std::log(log_zn / std::log(2)) / std::log(2);
					float mu = iteration + 1 - nu;

					if (mu < 0) {
						mu += amountColours;
					}

					int colourPicker = (int) std::floor(mu) % amountColours;
					int colourPicker2 = (1 + (int)std::floor(mu)) % amountColours;

				    auto& color1 = settings.getColours().at(colourPicker);
				    auto& color2 = settings.getColours().at(colourPicker2);

					color1->interpolate(color1, color2, interpolatedColour, mu - (long)mu);
					interpolatedColour.get()->toRGB(*interpolatedColour);

					auto r = (int) interpolatedColour->getR();
					auto g = (int) interpolatedColour->getG();
					auto b = (int) interpolatedColour->getB();

					Vec3b& colorAtPixel = image.at<cv::Vec3b>(y, x);
					// OpenCV uses BGR instead of RGB
					colorAtPixel[0] = b;
					colorAtPixel[1] = g;
					colorAtPixel[2] = r;
				}
			}
		}
		return image; 
	}
};

#endif