#include "SaveLogger.h"
#include <sstream>
#include <fstream>
#include "ConfigReader.h"
#include "GameLogger.h"
#include <windows.h>

int SaveLogger::index = 0;
ofstream SaveLogger::out = ofstream();
string SaveLogger::value[LENGTHOFVALUE][5] = { { "", "", "", "", "" } };
string SaveLogger::currentFilename = "";
int SaveLogger::curNumObjs = 0;

SaveLogger::SaveLogger()
{
	intialize();
}


SaveLogger::~SaveLogger()
{
}

bool SaveLogger::intialize(const char* filename)
{
	if (currentFilename == filename) return true;
	else
	{
		if (currentFilename != "")
		{
			for (int i = 0; i < LENGTHOFVALUE; i++)
			{
				for (int i2 = 0; i2 < 5; i2++)
				{
					value[i][i2] = " ";
				}
			}
		}
		currentFilename = filename;
	}
	stringstream buffer;
	ifstream meInput(filename);

	if (!meInput.good())
	{
		cout << "file failed to load..." << filename;
		exit(1);
	}
	buffer << meInput.rdbuf();
	string configFile = buffer.str();

	buffer = stringstream(configFile);
	string word;
	int i = 0;
	int i2 = 0;
	string s;
	bool inQuotes = false;
	while (buffer.good())
	{

		buffer >> word;
		if (!isComment(word))
		{

			value[i][i2] = word;
			buffer >> word;
			i2++;

			if (word[0] == '"')
			{
				word[0] = ' ';
				inQuotes = true;
				while (inQuotes)
				{
					for (unsigned int j = 1; j < word.length(); j++)
					{
						if (word[j] == '"')
						{
							inQuotes = false;
							word[j] = ' ';
							break;
						}
						else if (word[j] == ',')
						{
							value[i][i2] = s;
							s = "";
							i2++;
						}
						else
						{
							s += word[j];
						}

					}
					value[i][i2] = s;
					i2++;
					s = "";
				}
			}
			else
			{
				value[i][i2] = word;
			}


			if (i > LENGTHOFVALUE)
			{

				cout << "To many Keys In Save Logger File" << endl;
				return false;
			}
			i++;
			index++;
			i2 = 0;
		}
	}

	curNumObjs = GetNumObjs();
	GameLogger::log("Save Logger file loaded");
	out.open(filename, ios::out | ios::app);
	return true;
}

bool SaveLogger::isComment(string word)
{
	for (unsigned int i = 0; i < word.length(); i++)
	{
		if (word[i] == '/' && word[i + 1] == '/')
		{
			return true;
		}
	}
	return false;
}

void SaveLogger::log(std::string objName, std::string textureLocation, std::string sceneLocation,glm::vec3 position)
{
	if (index == LENGTHOFVALUE)
	{
		cout << "logger is to big" << endl;
		shutdownLog();
	}
	else
	{
		value[index][0] = objName;
		value[index][1] = textureLocation;
		value[index][2] = sceneLocation;
		float pos = position.x;
		stringstream ss(stringstream::in | stringstream::out);
		ss << pos;
		value[index][3] = ss.str();
		pos = position.y;
		ss = stringstream(stringstream::in | stringstream::out);
		ss << pos;
		value[index][4] = ss.str();
		pos = position.z;
		ss = stringstream(stringstream::in | stringstream::out);
		ss << pos;
		value[index][5] = ss.str();
		index++;
	}
}

void SaveLogger::shutdownLog()
{
	//out.open(currentFilename, ios::out | ios::app);
	//out.seekp(0);
	//for (int i = 0; i < index; i++)
	//{
	//	if (value[i][2] != "")
	//		out << value[i][0] << " " << '"' << value[i][1] << "," << value[i][2] << "," << value[i][3] << '"' << endl;
	//	else if (value[i][0] != "")
	//		out << value[i][0] << " " << value[i][1] << endl;
	//	else {
	//	}
	//}
	out.close();
}

int SaveLogger::GetNumObjs()
{
	int numObjs = 0;
	for (int i = 0; i < LENGTHOFVALUE; i++)
	{
		if (value[i][0] == "Name")
		{
			numObjs++;
		}
		if (value[i][0] == "")
		{
			break;
		}
	}
	return numObjs;
}

string SaveLogger::GetName(int objId)
{
	int currentObjId = -1;
	for (int i = 0; i < LENGTHOFVALUE; i++)
	{
		if (value[i][0] == "Name")
		{
			currentObjId++;
			if(currentObjId == objId)
			return value[i][1];
		}
	}
	GameLogger::log("could not find Name for Obj:" + objId);
	cout << "check log" << endl;
	return "0";
}

string SaveLogger::GetObj(string objName)
{
	for (int i = 0; i < LENGTHOFVALUE; i++)
	{
		if (value[i][1] == objName)
		{
			return value[i + 1][1];
		}
	}
	GameLogger::log("could not find Obj Type for Obj:" + objName);
	cout << "check log" << endl;
	return "0";
}

void SaveLogger::AddObj(string ObjName)
{
	out << "\n";

	value[index][0] = "Name";
	int numObjs = (GetNumObjs());
	ostringstream convert;
	convert << numObjs;
	value[index][1] = "DefaultObject" + convert.str();
	out << value[index][0] << " " << value[index][1] << "\n";

	index++;
	value[index][0] = "Obj";
	value[index][1] = ObjName;
	out << value[index][0] << " " << value[index][1] << "\n";

	index++;
	value[index][0] = "Position";
	value[index][1] = "0.0";
	value[index][2] = "0.0";
	value[index][3] = "0.0";
	out << value[index][0] << " " << '"' << value[index][1] << "," << value[index][2] << "," << value[index][3] << '"' << "\n";
}

glm::vec3 SaveLogger::GetPosition(string objName)
{
	for (int i = 0; i < LENGTHOFVALUE; i++)
	{
		if (value[i][1] == objName)
		{
			//GameLogger::log("key: " + pKey + " Value: " + value[i][1]);
			return glm::vec3(ConfigReader::GetFloatFromString(value[i+2][1]), ConfigReader::GetFloatFromString(value[i + 2][2]), ConfigReader::GetFloatFromString(value[i + 2][3]));
		}

	}
	GameLogger::log("could not find Position for Obj:" + objName);
	cout << "check log" << endl;
	return glm::vec3();
}

bool SaveLogger::ValueChanged()
{
	int newNumObjs = GetNumObjs();
	bool result = newNumObjs != curNumObjs;
	curNumObjs = newNumObjs;
	return result;
}
