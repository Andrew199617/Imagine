#include "GameLogger.h"

int GameLogger::index = 0;
bool GameLogger::initialized;
std::ofstream GameLogger::out;
std::string GameLogger::value[LENGTHOFVALUE] = { " " };

using std::ios;
using std::cout;
using std::endl;

GameLogger::GameLogger()
{

}


GameLogger::~GameLogger()
{
}

void GameLogger::Intialize(const char* filename)
{
	if (!initialized)
	{
		index = 0;
		out.open(filename, ios::out | ios::trunc);
		out.seekp(0);
	}
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
		string s = std::to_string(index) + ". " + msg;
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