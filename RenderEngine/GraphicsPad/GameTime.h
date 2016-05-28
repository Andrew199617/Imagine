#pragma once
#include <Windows.h>

class GameTime
{
public:
	bool initialize();
	bool shutdown();
	void newFrame();
	float timeElapsedLastFrame();
	float getGameTime();

	GameTime();
	~GameTime();
private:
	LARGE_INTEGER timeFrequency;
	LARGE_INTEGER timeLastFrame;
	LARGE_INTEGER deltaLastFrame;
	float deltaTime;
};

