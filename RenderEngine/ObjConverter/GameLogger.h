#pragma once
#include <string>
#include <fstream>
#include <ostream>
#include <iostream>

using namespace std;

static std::ofstream out;
static int index = 0;
static const int LENGTHOFVALUE = 50000;
static std::string value[LENGTHOFVALUE];

class GameLogger
{
public:
	GameLogger();
	~GameLogger();
	static void intialize(const char* filename = "..\\..\\StaticData\\ObjConverterLogger.txt");
	static void log(std::string msg);
	static void shutdownLog();
	
};

