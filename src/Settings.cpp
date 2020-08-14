/*
Settings is a Singleton which manages and stores all parameters
In addition also the interaction using the commandline is handled.
*/

#include "MandelBrot/Settings.hpp"
#include "MandelBrot/VariadicTable.hpp"
#include "MandelBrot/RGB.hpp"
#include "MandelBrot/HSV.hpp"
#include "MandelBrot/Constants.hpp"
#include <exception>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>

using namespace std::literals;

Settings::Settings() {
	// constructor sets all default values for the settings.
	// if new parameters are added - the help message and the initialization will automatically adapt to the new parameters
	this->parameters.insert({ "-RGB"s , std::make_pair(COLOUR_PROGRESSION_RGB, "Gibt die Farben an in folgender RGB Form an: int|int|int  int|int|int ... "s) });
	this->parameters.insert({ "-HSV"s , std::make_pair(COLOUR_PROGRESSION_RGB, "Gibt die Farben an in folgender HSV Form an: float|float|float"s) });
	this->parameters.insert({ "-x"s, std::make_pair(REAL_X, "R(c) des Bildmittelpunktes c."s)});
	this->parameters.insert({ "-y"s, std::make_pair(IMAG_Y, "J(c) des Bildmittelpunktes c."s)});
	this->parameters.insert({ "-d"s, std::make_pair(HORIZ_DIAMETER, "Horizontaler Durchmesser des abzubildenden Bereichs."s)});
	this->parameters.insert({ "-w"s, std::make_pair(WIDTH, "Breite in Pixeln."s)});
	this->parameters.insert({ "-h"s, std::make_pair(HEIGHT, "Hoehe in Pixeln."s)});
	this->parameters.insert({ "-i"s, std::make_pair(MAX_ITERATION, "Maximale Anzahl an Iterationen."s)});
	this->parameters.insert({ "-p"s , std::make_pair(COLOUR_PROGRESSION_RGB, "Farbprogression."s) });
	this->parameters.insert({ "-BurningShip"s , std::make_pair(0.f, "Das setzen dieses Parameters zeichnet das 'burning ship' Fraktal."s) });

	// standard RGB colours set 
	auto& colourVector = getColours();
	colourVector.push_back(std::make_unique<RGB>(25, 7, 26));
	colourVector.push_back(std::make_unique<RGB>(9, 1, 47));
	colourVector.push_back(std::make_unique<RGB>(4, 4, 73));
	colourVector.push_back(std::make_unique<RGB>(0, 7, 100));
	colourVector.push_back(std::make_unique<RGB>(12, 44, 138));
	colourVector.push_back(std::make_unique<RGB>(24, 82, 177));
	colourVector.push_back(std::make_unique<RGB>(57, 125, 209));
	colourVector.push_back(std::make_unique<RGB>(134, 181, 229));
	colourVector.push_back(std::make_unique<RGB>(211, 236, 248));
	colourVector.push_back(std::make_unique<RGB>(241, 233, 191));
	colourVector.push_back(std::make_unique<RGB>(248, 201, 95));
	colourVector.push_back(std::make_unique<RGB>(255, 170, 0));
	colourVector.push_back(std::make_unique<RGB>(204, 128, 0));
	colourVector.push_back(std::make_unique<RGB>(153, 87, 0));
	colourVector.push_back(std::make_unique<RGB>(106, 52, 3));
	colourVector.push_back(std::make_unique<RGB>(66, 30, 15));
}

Settings::~Settings(){}

Settings& Settings::getInstance() {
	static Settings settings;
	return settings;
}

void Settings::initialize(const int argc, const char* argv[]) {

	bool printHelpMessage = false;
	bool customProgression = false;

	if (isInitialized == true) {
		std::cout << "Settings sollte nicht zweimal initialisiert werden..." << std::endl;
	}
	else if (argc < 2) {
		std::cout << "Standardmaessig wird die Tag-Nacht RGB Reihenfolge verwendet." << std::endl;
	}
	else {
		for (size_t i = 0; i < argc; i++) {

			if (std::string(argv[i]) == "-?") { printHelpMessage = true; }
			if (std::string(argv[i]) == "-p") { customProgression = true; }

			std::map<std::string, std::pair<double, std::string>>::iterator it;
			it = parameters.find(std::string(argv[i]));

			// if parameter was found -> overwrite the default value with the given one
			if (it != parameters.end()) {
				it->second.first = atof(argv[i + 1]);
			}
		}

		if (std::string(argv[1]) == "-RGB") {
			rgbSpace = true;
			if (!customProgression) {
				parameters.find(std::string("-p"))->second.first = COLOUR_PROGRESSION_RGB;
			}
			int counter = 2;
			getColours().clear();
			//while the RGB parameters still exist (either end of params or next parameter)
			while (counter < argc && std::string(argv[counter]).length() != 2) {
				
				auto values = split(std::string(argv[counter]), '|');
				float red = std::stof(values.at(0));
				float green = std::stof(values.at(1));
				float blue = std::stof(values.at(2));
				
				getColours().push_back(std::make_unique<RGB>(red, green, blue));

				counter++;
			}
		}

		if (std::string(argv[1]) == "-HSV") {
			rgbSpace = false;
			if (!customProgression) {
				parameters.find(std::string("-p"))->second.first = COLOUR_PROGRESSION_HSV; 
			}
			auto values = split(std::string(argv[2]),'|');
			float hue = std::stof(values.at(0));
			float saturation = std::stof(values.at(1));
			float value = std::stof(values.at(2));

			getColours().clear();
			getColours().push_back(std::make_unique<HSV>(hue,saturation,value));
		}
	}

	if (printHelpMessage == true) {
		Settings::printHelpMessage();
		exit(0);
	}

	isInitialized = true;
}

void Settings::printHelpMessage() {

	// !! VariadicTable taken from https://github.com/friedmud/variadic_table !!
	VariadicTable <std::string, std::string, double> vt({ "Parameter", "Beschreibung", "Standardwert" });

	for (auto const& [parameter, content] : parameters) {
		vt.addRow( parameter, content.second, content.first );
	}

	std::cout << "Das Programm visualisiert das Mandelbrot oder BurningShip Fraktal." << std::endl;
	std::cout << "Falls Farben angegeben werden, muessen diese als erster Parameter uebergeben werden." << std::endl;
	std::cout << "Folgende Tabelle zeigt die Anzahl an moeglichen Parametern an." << std::endl;
	vt.print(std::cout);

}

// bunch of getters for easier access
const double Settings::getReal() const {
	return parameters.find("-x"s)->second.first;
}

const double Settings::getImag() const {
	return parameters.find("-y"s)->second.first;
}

const double Settings::getHorizDiameter() const {
	return parameters.find("-d"s)->second.first;
}

const int Settings::getWidth() const {
	return int (parameters.find("-w"s)->second.first);
}

const int Settings::getHeight() const {
	return int (parameters.find("-h"s)->second.first);
}

const int Settings::getMaxIterations() const {
	return int (parameters.find("-i"s)->second.first);
}

const float Settings::getColourProgression() const {
	return float (parameters.find("-p"s)->second.first);
}

const bool Settings::isRGBSpace() const
{
	return this->rgbSpace;
}

 Settings::Colours& Settings::getColours() {
	return colours;
}

 // Splits a string by a delimiter and returns the resulting string vector
 // source https://stackoverflow.com/a/27511119/9919242
 std::vector<std::string> Settings::split(const std::string& s, char delim) {
	 std::stringstream ss(s);
	 std::string item;
	 std::vector<std::string> elems;
	 while (std::getline(ss, item, delim)) {
		 elems.push_back(std::move(item)); 
	 }
	 return elems;
 }