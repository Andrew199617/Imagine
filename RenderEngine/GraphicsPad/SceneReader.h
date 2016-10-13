#pragma once
#include <string>
#pragma warning(push)
#pragma warning(disable : 4201)
#include <glm.hpp>
#pragma warning(pop)
struct Scene;
struct AnimationScene;

using glm::vec3;
using namespace std;

class SceneReader
{
public:
	SceneReader();
	~SceneReader();
	AnimationScene* ReadAnimationSceneFile(string filename);
	Scene* ReadSceneFile(string filename);
	void DisplayVec3(vec3* vec);
	void DisplayScene(Scene* scene);
};

