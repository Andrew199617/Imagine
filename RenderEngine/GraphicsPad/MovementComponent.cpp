#include "MovementComponent.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm.hpp>
#pragma warning(pop)
#include "GravityComponent.h"

MovementComponent::MovementComponent(float Speed)
{
	if (Speed == 0.0f)
	{
		string s = ConfigReader::findNeededValueForKey("CameraStrafeSpeed");
		this->strafeSpeed = (float)atoi(s.c_str());
	}
	else
	{
		this->strafeSpeed = Speed;
	}
}


MovementComponent::~MovementComponent()
{
}

bool MovementComponent::Initialize()
{
	//checkNeededComponents();
	return true;
}

void MovementComponent::checkNeededComponents(SpatialComponent* spatial, CameraComponent* camera)
{
	if (!spatial)
	{
		string s = ": can not obtain Spatial Component";
		GameLogger::log(this->GetName() + s);
		GameLogger::shutdownLog();
		exit(1);
	}
	if (!camera)
	{
		string s = ": can not obtain Spatial Component";
		GameLogger::log(this->GetName() + s);
		GameLogger::shutdownLog();
		exit(1);
	}
}

void MovementComponent::moveForward(float dt)
{
	SpatialComponent* spatialcomponent = this->GetSiblingComponent<SpatialComponent>();
	CameraComponent* cameraComponent = this->GetSiblingComponent<CameraComponent>();
	checkNeededComponents(spatialcomponent, cameraComponent);

	spatialcomponent->position.x += (strafeSpeed * cameraComponent->viewDirection * dt).x;
	spatialcomponent->position.z += (strafeSpeed * cameraComponent->viewDirection * dt).z;
}

void MovementComponent::moveForward(float dt,glm::vec3 viewDirection)
{
	SpatialComponent* spatialcomponent = this->GetSiblingComponent<SpatialComponent>();
	if (!spatialcomponent)
	{
		string s = ": can not obtain Spatial Component";
		GameLogger::log(this->GetName() + s);
		GameLogger::shutdownLog();
		exit(1);
	}
	spatialcomponent->position.x += (strafeSpeed * viewDirection * dt).x;
	spatialcomponent->position.z += (strafeSpeed * viewDirection * dt).z;
}

void MovementComponent::moveBackward(float dt)
{
	SpatialComponent* spatialcomponent = this->GetSiblingComponent<SpatialComponent>();
	CameraComponent* cameraComponent = this->GetSiblingComponent<CameraComponent>();
	checkNeededComponents(spatialcomponent, cameraComponent);
	spatialcomponent->position.x += (-strafeSpeed * cameraComponent->viewDirection * dt).x;
	spatialcomponent->position.z += (-strafeSpeed * cameraComponent->viewDirection * dt).z;
}

void MovementComponent::strafeLeft(float dt)
{
	SpatialComponent* spatialcomponent = this->GetSiblingComponent<SpatialComponent>();
	CameraComponent* cameraComponent = this->GetSiblingComponent<CameraComponent>();
	checkNeededComponents(spatialcomponent, cameraComponent);

	glm::vec3 strafeDirection = glm::cross(cameraComponent->viewDirection, spatialcomponent->UP);

	spatialcomponent->position.x += (-strafeSpeed * strafeDirection * dt).x;
	spatialcomponent->position.z += (-strafeSpeed * strafeDirection * dt).z;
}

void MovementComponent::strafeRight(float dt)
{
	SpatialComponent* spatialcomponent = this->GetSiblingComponent<SpatialComponent>();
	CameraComponent* cameraComponent = this->GetSiblingComponent<CameraComponent>();
	checkNeededComponents(spatialcomponent, cameraComponent);

	glm::vec3 strafeDirection = glm::cross(cameraComponent->viewDirection, spatialcomponent->UP);

	spatialcomponent->position.x += (strafeSpeed * strafeDirection * dt).x;
	spatialcomponent->position.z += (strafeSpeed * strafeDirection * dt).z;
}

void MovementComponent::moveUp(float dt)
{
	SpatialComponent* spatialcomponent = this->GetSiblingComponent<SpatialComponent>();
	if (!spatialcomponent)
	{
		string s = ": can not obtain Spatial Component";
		GameLogger::log(this->GetName() + s);
		GameLogger::shutdownLog();
		exit(1);
	}
	spatialcomponent->position.y += (strafeSpeed * spatialcomponent->UP * dt).y;
}

void MovementComponent::moveDown(float dt)
{
	SpatialComponent* spatialcomponent = this->GetSiblingComponent<SpatialComponent>();
	if (!spatialcomponent)
	{
		string s = ": can not obtain Spatial Component";
		GameLogger::log(this->GetName() + s);
		GameLogger::shutdownLog();
		exit(1);
	}
	spatialcomponent->position.y += (-strafeSpeed * spatialcomponent->UP * dt).y;
}

void MovementComponent::Jump(int time, float dt)
{
	static float m_dt = 0;
	m_dt += dt;
	if (m_dt > time)
	{
		if (m_dt < (float)time * 1.9)
		{
			moveDown(dt);
		}
		else {
			m_dt = 0;
		}
	}
	else
	{
		moveUp(dt);
	}
}