#pragma once
#include <string>
#include <sstream>
#pragma warning(push)
#pragma warning(disable : 4201)
#include <glm.hpp>
#pragma warning(pop)

using namespace std;


class ConfigReader
{
public:
	ConfigReader();
	bool Initialize(const char* filename = "..\\Data\\Config.txt");
	bool isComment(string word);
	string findValueForKey(string pKey);
	string findNeededValueForKey(string pKey);
	glm::vec3 findVec3ForKey(string pKey);
	glm::vec2 findVec2ForKey(string pKey);
	float GetFloatFromString(string s) const;
	int GetIntFromString(string s) const;
	bool GetBoolFromString(string s) const;
	bool Shutdown();

private:
	static const int LENGTHOFVALUE = 92;
	string configFile;
	string value[LENGTHOFVALUE][5];
};
