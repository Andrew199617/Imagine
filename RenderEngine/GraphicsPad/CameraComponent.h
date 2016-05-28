#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm.hpp>
#pragma warning(pop)
#include "ConfigReader.h"
#include "Component.h"

class CameraComponent : 
	public Component
{
	
	
public:
	CameraComponent();
	glm::mat4 getWorldToViewMatrix();
	bool mouseUpdate();

	virtual bool Update(float dt) override;
	virtual bool Initialize() override;
	glm::vec3 position;
	glm::vec3 viewDirection;
	float rotateSpeed;
	float Zoffset;
	float Yoffset;
};

