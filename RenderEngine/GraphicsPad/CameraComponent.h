#pragma once
#include "ImgnComponent.h"
#include "glm.hpp"

class CameraComponent : 
	public ImgnComponent
{
	
	
public:
	CameraComponent();
	glm::mat4 getWorldToViewMatrix();
	bool mouseUpdate();

	virtual void Update(float dt) override;
	virtual bool Initialize() override;
	glm::vec3 position;
	glm::vec3 viewDirection;
	float rotateSpeed;
	float Zoffset;
	float Yoffset;
};

