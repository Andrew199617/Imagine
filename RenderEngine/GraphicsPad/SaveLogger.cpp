#include "SaveLogger.h"
#include <sstream>
#include "ConfigReader.h"
#include "GameLogger.h"

int SaveLogger::index = 0;
ofstream SaveLogger::out = ofstream();
string SaveLogger::value[LENGTHOFVALUE][5] = { { " ", " ", " ", " ", " " } };
bool SaveLogger::alreadyInitialized = false;

SaveLogger::SaveLogger()
{
	intialize();
}


SaveLogger::~SaveLogger()
{
}

bool SaveLogger::intialize(const char* filename)
{
	if (alreadyInitialized) return true;
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
					for (unsigned int j = 0; j < word.length(); j++)
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
			i2 = 0;
		}
	}

	GameLogger::log("Save Logger file loaded");
	alreadyInitialized = true;
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

	for (int i = 0; i < index; i++)
	{
		out << '"' + value[i][0] + '"' << " " << '"' + value[i][1] + '"' << " " << '"' + value[i][2] + '"' << " " << '"' + value[i][3] + '"' << " " << '"' + value[i][4] + '"' << 
			" " << '"' + value[i][5] + '"' << endl;
	}
	out.close();
}

int SaveLogger::GetNumObjs()
{
	int numObjs = 0;
	for (int i = 0; i < LENGTHOFVALUE; i++)
	{
		if (value[i][0] == "name")
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
		if (value[i][0] == "name")
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
