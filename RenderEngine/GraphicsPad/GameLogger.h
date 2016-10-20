#pragma once
#include <string>
#include <fstream>
#include <ostream>
#include <iostream>

using std::ofstream;
using std::string;

class GameLogger
{
public:
	GameLogger();
	~GameLogger();
	static void Intialize(const char* filename = "..\\Data\\GameLogger.txt");
	static void log(std::string msg);
	static void shutdownLog();
	
private:
	static std::ofstream out;
	static int index;
	static const int LENGTHOFVALUE = 50000;
	static std::string value[LENGTHOFVALUE];
	static bool initialized;
};

