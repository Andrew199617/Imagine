#include "ConfigReader.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include "GameLogger.h"

ConfigReader* ConfigReader::configReader = 0;

using std::stringstream;
using std::ifstream;
using std::cout;
using std::endl;

ConfigReader::ConfigReader()
{
	Initialize();
}

void ConfigReader::Initialize(const char* filename)
{
	stringstream buffer;
	ifstream meInput(filename);

	if (!meInput.good())
	{
		cout << "file failed to load..." << filename;
		exit(1);
	}
	buffer << meInput.rdbuf();
	configFile = buffer.str();

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

				cout << "To many Keys In Config File" << endl;
			}
			i++;
			i2 = 0;
		}
	}

	GameLogger::log("Config file loaded");
}

bool ConfigReader::isComment(string word)
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


string ConfigReader::findValueForKey(string pKey)
{
	for (int i = 0; i < LENGTHOFVALUE; i++)
	{
		if (value[i][0] == pKey)
		{
			//GameLogger::log("key: " + pKey + " Value: " + value[i][1]);
			return value[i][1];
		}

	}
	GameLogger::log("No value found for key: " + pKey);
	return "0";
}

string ConfigReader::findNeededValueForKey(string pKey)
{
	string result = findValueForKey(pKey);
	if (result.c_str() == 0)
	{
		cout << "No Value Found for Key: " << pKey << endl;
		GameLogger::log("No value found for key: " + pKey);
		GameLogger::shutdownLog();
		exit(EXIT_FAILURE);
	}
	return result;
}

glm::vec3 ConfigReader::findVec3ForKey(string pKey)
{
	for (int i = 0; i < LENGTHOFVALUE; i++)
	{
		if (value[i][0] == pKey)
		{
			//GameLogger::log("key: " + pKey + " Value: " + value[i][1]);
			return glm::vec3(GetFloatFromString(value[i][1]), GetFloatFromString(value[i][2]), GetFloatFromString(value[i][3]));
		}

	}
	GameLogger::log("could not find vec3 for key:" + pKey);
	cout << "check log" << endl;
	return glm::vec3();
}

glm::vec2 ConfigReader::findVec2ForKey(string pKey)
{
	for (int i = 0; i < LENGTHOFVALUE; i++)
	{
		if (value[i][0] == pKey)
		{
			//GameLogger::log("key: " + pKey + " Value: " + value[i][1]);
			return glm::vec2(GetFloatFromString(value[i][1]), GetFloatFromString(value[i][2]));
		}

	}
	GameLogger::log("could not find vec2 for key:" + pKey);
	cout << "check log" << endl;
	return glm::vec2();
}

float ConfigReader::GetFloatFromString(string s)
{
	std::istringstream buffer(s);
	float m_value;
	buffer >> m_value;
	return m_value;
}

int ConfigReader::GetIntFromString(string s)
{
	std::istringstream buffer(s);
	int m_value;
	buffer >> m_value;
	return m_value;
}

bool ConfigReader::GetBoolFromString(string s)
{
	std::istringstream buffer(s);
	bool m_value;
	buffer >> m_value;
	return m_value;
}

bool ConfigReader::Shutdown()
{
	return true;
}