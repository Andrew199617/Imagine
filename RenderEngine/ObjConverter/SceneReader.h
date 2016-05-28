#pragma once
#include "Scene.h"
#pragma warning(push)
#pragma warning(disable : 4201)
#include <glm.hpp>
#pragma warning(pop)

using namespace glm;
using namespace std;

class SceneReader
{
public:
	SceneReader();
	~SceneReader();
	Scene* ReadSceneFile(const char* filename);
	void DisplayVec3(vec3* vec);
	void DisplayScene(Scene* scene);
};

