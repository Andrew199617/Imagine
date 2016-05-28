#include "SaveLogger.h"
#include <sstream>

int SaveLogger::index = 0;
ofstream SaveLogger::out = ofstream();
string SaveLogger::value[LENGTHOFVALUE][6] = { { " ", " ", " ", " ", " ", " " } };

SaveLogger::SaveLogger()
{
	intialize();
}


SaveLogger::~SaveLogger()
{
}

void SaveLogger::intialize(const char* filename)
{
	stringstream buffer;
	ifstream meInput(filename);
	int index1 = 0;
	if (!meInput.good())
	{
		cout << "file failed to load..." << filename;
	}
	else
	{
		buffer << meInput.rdbuf();
		string word;
		string temp;
		int need2 = 0;
		
		int index2 = 0;
		while (buffer.good())
		{
			buffer >> word;
			for (int i = 0; i < (int) word.length(); i++)
			{
				if (need2 == 2)
				{
					break;
				}
				if (word[i] == '"')
				{
					
					need2++;
				}
				else
				{
					temp += word[i];
				}
			}
			if (need2 == 2)
			{
				need2 = 0;
				value[index1][index2] = temp;
				temp = string();
				index2++;
				if (index2 == 6)
				{
					index2 = 0; index1++;
				}
			}
			else if (need2 == 1)
			{
				temp += ' ';
			}


		}
	}
	

	index = index1;
	out.open(filename, ios::out | ios::trunc);
	out.seekp(0);
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

string SaveLogger::getTextureWithKey(string key)
{
	for (int i = 0; i < index; i++)
	{
		if (value[i][0] == key)
		{
			return value[i][1];
		}
	}
	return 0;
}

string SaveLogger::getSceneWithKey(string key)
{
	for (int i = 0; i < index; i++)
	{
		if (value[i][0] == key)
		{
			return value[i][2];
		}
	}
	return 0;
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