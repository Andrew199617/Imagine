#pragma once
#include "TransformLayout.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm.hpp>
#pragma warning(pop)
#include "RenderEngine\TransformInfo.h"

class SpatialComponent :
	public TransformLayout
{
	
public:
	SpatialComponent();
	~SpatialComponent();
	void SetPosition(glm::vec3 Position);
	void SetScale(glm::vec3 Scale);
	void SetRotate(glm::vec3 Rotate);
	inline glm::vec3 GetRotate() { return rotate; }
	inline glm::vec3 GetScale() { return scale; }

	glm::vec3 position;
	glm::vec3 velocity;
	const glm::vec3 UP;

private:
	TransformInfo* transformInfo;
	glm::vec3 scale;
	glm::vec3 rotate;
};

