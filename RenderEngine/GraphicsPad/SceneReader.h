#pragma once
#include <string>
#pragma warning(push)
#pragma warning(disable : 4201)
#include <glm.hpp>
#pragma warning(pop)
struct Scene;

using namespace glm;
using namespace std;

class SceneReader
{
public:
	SceneReader();
	~SceneReader();
	Scene* ReadSceneFile(string filename);
	void DisplayVec3(vec3* vec);
	void DisplayScene(Scene* scene);
};

