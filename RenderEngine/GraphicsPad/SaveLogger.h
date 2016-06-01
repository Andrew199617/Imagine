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
	static bool intialize(const char* filename = "..\\Data\\SaveLogger.txt");
	static bool isComment(string word);
	static void log(std::string objName, std::string textureLocation, string, glm::vec3 position);
	static void shutdownLog();
	static std::ofstream out;
	static int index;
	static const int LENGTHOFVALUE = 50000;
	static std::string value[LENGTHOFVALUE][5];
	static int GetNumObjs();
	static string GetName(int);
	static string GetObj(string);
	static void AddObj(string);
	static glm::vec3 GetPosition(string);
	static bool ValueChanged();
private:
	static string currentFilename;
	static bool reInitialized;
	static int numDefaultObjs;
	
};