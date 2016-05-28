#include "GameTime.h"

#pragma warning(push)
#pragma warning(disable:4800)
bool GameTime::initialize()
{
	bool b = QueryPerformanceFrequency(&timeFrequency);
	if (!b)
		return false;
	return QueryPerformanceCounter(&timeLastFrame);
}
#pragma warning(pop)

bool GameTime::shutdown(){ return true; }

void GameTime::newFrame()
{
	LARGE_INTEGER thisTime;
	QueryPerformanceCounter(&thisTime);
	LARGE_INTEGER delta;
	delta.QuadPart = thisTime.QuadPart - timeLastFrame.QuadPart;
	deltaTime = ((float)delta.QuadPart) / timeFrequency.QuadPart;
	timeLastFrame.QuadPart = thisTime.QuadPart;
}

float GameTime::timeElapsedLastFrame()
{
	return deltaTime;
}

float GameTime::getGameTime()
{
	return -1;
}

GameTime::GameTime()
{
	initialize();
}


GameTime::~GameTime()
{
}
