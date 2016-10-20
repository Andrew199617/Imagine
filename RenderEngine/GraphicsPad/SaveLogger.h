#pragma once
#include <string>
#include <fstream>
#include <ostream>
#include <iostream>
#include "fwd.hpp"

namespace Imgn
{
	const int LENGTHOFVALUE = 50000;
}

using std::string;
using std::ofstream;

class SaveLogger
{
	SaveLogger() { Intialize(); }
	~SaveLogger();
public:
	static SaveLogger* Instance() { if (!saveLogger) { saveLogger = new SaveLogger(); } return saveLogger; }
	void Intialize(const char* filename = "..\\Data\\SaveLogger.txt");
	void log(std::string objName, std::string textureLocation, string, glm::vec3 position);
	void shutdownLog();
	int GetNumObjs();
	string GetName(int);
	string GetObj(string);
	void AddObj(string);
	glm::vec3 GetPosition(string);
	glm::vec3 GetRotate(string);
	glm::vec3 GetScale(string);
	bool ValueChanged();
private:
	static SaveLogger* saveLogger;
	bool isComment(string word);

	ofstream out;
	int index;
	string value[Imgn::LENGTHOFVALUE][5];
	string currentFilename;
	int curNumObjs;
	
};