#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#pragma warning (disable:4458)
#include <glm.hpp>
#pragma warning(pop)
#include "..\CameraComponent.h"

class TransformInfo
{
public:
	TransformInfo(){}
	TransformInfo(glm::vec3 m_translateTransform , glm::vec3 m_scaleTransform, float angle,
		glm::vec3 m_rotateTransform);
	~TransformInfo();
	static glm::mat4 WorldToViewMatrix;
	static glm::mat4 projectionMatrix;
	glm::mat4 m_scaleTransform;
	glm::mat4 m_rotateTransform;
	glm::mat4 m_translateTransform;
	
};

