#pragma once
#include <string>

class SceneMaker
{
public:
	SceneMaker();
	~SceneMaker();
	static void makeScene(std::string filenamem, std::string objName, int sceneVertexFormat);
};

