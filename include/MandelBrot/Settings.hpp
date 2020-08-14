/*
Settings is a Singleton which manages and stores all parameters
In addition also the interaction using the commandline is handled.
*/
#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <map>
#include <string>
#include <vector>
#include "Constants.hpp"
#include "ColourSpace.hpp"
#include <memory>

class Settings
{
public:
	using ValueAndHelp = std::pair<double, std::string>;
	using ParameterMap = std::map<std::string, ValueAndHelp>;
	using Colours = std::vector<ColourSpace::ColourSpacePtr>;

	Settings(const Settings&) = delete;    // deactivating this constructor 
	Settings& operator=(const Settings&) = delete; // deactivating this constructor 
	~Settings();

	static Settings& getInstance();

	void initialize(const int argc, char const* argv[]);
	
	ParameterMap parameters;
	Colours colours;

	const double getReal() const;
	const double getImag() const;
	const double getHorizDiameter() const;
	const int    getWidth() const;
	const int    getHeight() const;
	const int    getMaxIterations() const;
	const float  getColourProgression() const;
	const bool   isRGBSpace() const;
	std::vector<std::string> split(const std::string& s, char delim);

	Colours& getColours();

private:
	Settings();
	void printHelpMessage(); 
	bool rgbSpace = true;
	bool isInitialized = false;

};

#endif