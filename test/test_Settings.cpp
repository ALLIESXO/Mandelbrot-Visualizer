#include <gtest/gtest.h> // googletest header file
#include "MandelBrot/Settings.hpp"
#include "MandelBrot/Constants.hpp"
#include <iostream>


TEST(Settings, testParameterDefaultValue) {

	Settings& settings(Settings::getInstance());

	EXPECT_EQ(settings.parameters.find(std::string("-d"))->second.first, HORIZ_DIAMETER);
	EXPECT_EQ(settings.parameters.find(std::string("-x"))->second.first, REAL_X);
	EXPECT_EQ(settings.parameters.find(std::string("-y"))->second.first, IMAG_Y);
	EXPECT_EQ(settings.parameters.find(std::string("-w"))->second.first, WIDTH);
	EXPECT_EQ(settings.parameters.find(std::string("-h"))->second.first, HEIGHT);
	EXPECT_EQ(settings.parameters.find(std::string("-i"))->second.first, MAX_ITERATION);
	EXPECT_EQ(settings.parameters.find(std::string("-p"))->second.first, COLOUR_PROGRESSION_RGB);

}

TEST(Settings, testGetters) {
	Settings& setting(Settings::getInstance());

	EXPECT_DOUBLE_EQ(setting.getHorizDiameter(), HORIZ_DIAMETER);
	EXPECT_DOUBLE_EQ(setting.getReal(), REAL_X);
	EXPECT_DOUBLE_EQ(setting.getImag(), IMAG_Y);
	EXPECT_EQ(setting.getColourProgression(), COLOUR_PROGRESSION_RGB);
	EXPECT_EQ(setting.getHeight(), HEIGHT);
	EXPECT_EQ(setting.getWidth(), WIDTH);
	EXPECT_EQ(setting.getMaxIterations(), MAX_ITERATION);
	// check if this works
	EXPECT_FALSE(setting.getColours().at(0) == nullptr);
}

TEST(Settings, testSettingsIsSingleton) {
	Settings& ref1(Settings::getInstance());
	Settings& ref2(Settings::getInstance());

	EXPECT_EQ(&ref1, &ref2);
}

TEST(Settings, testSettingsInitialization) {
	
	Settings& settings(Settings::getInstance());
	const char* test_params[] = {"RGB", "(52,231,111)","-x","0.5","-y","0.1", "-d", "2.5", "-w", "300", "-h", "500", "-i","5", "-p", "35"};
	settings.initialize(16 , test_params);

	EXPECT_EQ(settings.parameters.find(std::string("-d"))->second.first, 2.5);
	EXPECT_EQ(settings.parameters.find(std::string("-x"))->second.first, 0.5);
	EXPECT_EQ(settings.parameters.find(std::string("-y"))->second.first, 0.1);
	EXPECT_EQ(settings.parameters.find(std::string("-w"))->second.first, 300.0);
	EXPECT_EQ(settings.parameters.find(std::string("-h"))->second.first, 500.0);
	EXPECT_EQ(settings.parameters.find(std::string("-i"))->second.first, 5.0);
	EXPECT_EQ(settings.parameters.find(std::string("-p"))->second.first, 35.0);
}
