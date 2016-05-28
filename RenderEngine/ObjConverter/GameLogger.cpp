#include "GameLogger.h"

GameLogger::GameLogger()
{
	intialize();
}


GameLogger::~GameLogger()
{
}

void GameLogger::intialize(const char* filename)
{
	index = 0;
	out.open(filename, ios::out | ios::trunc);
	out.seekp(0);
}

void GameLogger::log(std::string msg)
{
	if (index == LENGTHOFVALUE)
	{
		cout << "logger is to big" << endl;
		shutdownLog();
	}
	else
	{
		string s = to_string(index) + ". " + msg;
		value[index] = s;
		index++;
	}
}

void GameLogger::shutdownLog()
{
	
	for (int i = 0; i < index; i++)
	{
		out << value[i] << endl;
	}
	out.close();
}