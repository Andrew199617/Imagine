#pragma once
#include <string>
#include <sstream>
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm.hpp>
#pragma warning(pop)

using namespace std;


class ConfigReader
{
public:
	ConfigReader();
	static bool Initialize(const char* filename = "..\\Data\\Config.txt");
	static bool isComment(string word);
	static string findValueForKey(string pKey);
	static string findNeededValueForKey(string pKey);
	static glm::vec3 findVec3ForKey(string pKey);
	static glm::vec2 findVec2ForKey(string pKey);
	static float GetFloatFromString(string s);
	static int GetIntFromString(string s);
	static bool GetBoolFromString(string s);
	static bool Shutdown();

private:
	static const int LENGTHOFVALUE = 92;
	static string configFile;
	static string value[LENGTHOFVALUE][5];
	static bool alreadyInitialized;
};