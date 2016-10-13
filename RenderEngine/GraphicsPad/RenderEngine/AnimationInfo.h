#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm.hpp>
#pragma warning(pop)
#include "fbxsdk.h"

class AnimationInfo
{
public:
	AnimationInfo();
	~AnimationInfo();
	void IncrementCurrentFrame() { currentFrame++; if (currentFrame > animationLength) currentFrame = 0; }
	int currentFrame;
	bool hasAnimation;
	int animationLength;
	int numKeys;
	FbxTime* keys;
	glm::mat4* animationData;
};

