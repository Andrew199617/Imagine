#pragma once
#include <string>
#include "glm.hpp"

using std::string;

class ConfigReader
{
	ConfigReader();
public:
	static ConfigReader* Instance() { 
		if (!configReader) 
		{ configReader = new ConfigReader(); }
		return configReader; }
	
	string findValueForKey(string pKey);
	string findNeededValueForKey(string pKey);
	glm::vec3 findVec3ForKey(string pKey);
	glm::vec2 findVec2ForKey(string pKey);
	float GetFloatFromString(string s);
	int GetIntFromString(string s);
	bool GetBoolFromString(string s);
	bool Shutdown();

private:
	void Initialize(const char* filename = "..\\Data\\Config.txt");
	bool isComment(string word);
	static ConfigReader* configReader;
	string configFile;
	static const int LENGTHOFVALUE = 92;
	string value[LENGTHOFVALUE][5];
};