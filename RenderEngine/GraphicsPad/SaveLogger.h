#pragma once
#include <string>
#include <fstream>
#include <ostream>
#include <iostream>
#pragma warning(push)
#pragma warning (disable:4201)
#include "glm.hpp"
#pragma warning(pop)

using namespace std;



class SaveLogger
{
public:
	SaveLogger();
	~SaveLogger();
	static void intialize(const char* filename = "..\\..\\StaticData\\SaveLogger.txt");
	static void log(std::string objName, std::string textureLocation, string, glm::vec3 position);
	static string getTextureWithKey(string key);
	static string getSceneWithKey(string key);
	static void shutdownLog();
	static std::ofstream out;
	static int index;
	static const int LENGTHOFVALUE = 50000;
	static std::string value[LENGTHOFVALUE][6];

};