#include "CameraComponent.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include "gtx\transform.hpp"
#pragma warning(pop)
#include "GameLogger.h"
#include "MouseComponent.h"
#include "SpatialComponent.h"

CameraComponent::CameraComponent() 
{
	ConfigReader::Initialize();
	viewDirection = ConfigReader::findVec3ForKey("CameraViewDirection");
	string s = ConfigReader::findNeededValueForKey("CameraRotateSpeed");
	this->rotateSpeed = (float)atoi(s.c_str());
}

bool CameraComponent::mouseUpdate()
{
	MouseComponent* mouse = this->GetSiblingComponent<MouseComponent>();
	SpatialComponent* spatial = this->GetSiblingComponent<SpatialComponent>();
	if (!mouse || !spatial)
	{
		string s = ": can not obtain a Component";
		GameLogger::log(this->GetName() + s);
		GameLogger::shutdownLog();
		exit(1);
	}

	glm::vec2 mouseDelta = mouse->GetMouseDelta();
	
	if (glm::length(mouseDelta) > 50.0f)
	{
		mouse->setOldMousePosition();
		return false;
	}
	
	glm::vec3 toRotateAround = glm::cross(viewDirection, spatial->UP);

	viewDirection = glm::mat3(glm::rotate(-mouseDelta.x * rotateSpeed, spatial->UP) * glm::rotate(-mouseDelta.y * rotateSpeed , toRotateAround))  * viewDirection;

	mouse->setOldMousePosition();
	return true;
}

bool CameraComponent::Update(float dt)
{
	SpatialComponent* spatial = this->GetSiblingComponent<SpatialComponent>();
	if (!spatial)
	{
		string s = ": can not obtain spatial Component";
		GameLogger::log(this->GetName() + s);
		return false;
	}
	this->position = spatial->position;
	this->position.z += Zoffset;
	this->position.y += Yoffset;
	dt;
	return true;
}

bool CameraComponent::Initialize()
{
	SpatialComponent* spatial = this->GetSiblingComponent<SpatialComponent>();
	if (!spatial)
	{
		string s = ": can not obtain spatial Component";
		GameLogger::log(this->GetName() + s);
		GameLogger::shutdownLog();
		return false;
	}
	spatial->position = ConfigReader::findVec3ForKey("CameraPosition");
	Zoffset = 0;
	Yoffset = 5.0;
	return true;
}

glm::mat4 CameraComponent::getWorldToViewMatrix()
{
	return glm::lookAt(position, position + viewDirection, this->GetSiblingComponent<SpatialComponent>()->UP );
}

//const float MOVEMENT_SPEED = 3.0f;
