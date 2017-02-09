#include "MovementComponent.h"
#include "glm.hpp"
#include "GravityComponent.h"
#include "ConfigReader.h"
#include "Physics\RigidBody.h"
#include <windows.h>
#include "ImgnConstants.hpp"

MovementComponent::~MovementComponent()
{
}

bool MovementComponent::Initialize()
{
	if (strafeSpeed == 0.0f)
	{
		string s = ConfigReader::Instance()->findNeededValueForKey("CameraStrafeSpeed");
		this->strafeSpeed = (float)atoi(s.c_str());
	}
	return true;
}

void MovementComponent::checkNeededComponents(ImgnComponent* spatial, ImgnComponent* camera)
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

	glm::vec3 pos = spatialcomponent->GetPosition();
	pos.x += (strafeSpeed * cameraComponent->viewDirection * dt).x;
	pos.z += (strafeSpeed * cameraComponent->viewDirection * dt).z;
	spatialcomponent->SetPosition(pos);
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

	glm::vec3 pos = spatialcomponent->GetPosition();
	pos.x += (strafeSpeed * viewDirection * dt).x;
	pos.z += (strafeSpeed * viewDirection * dt).z;
	spatialcomponent->SetPosition(pos);
}

void MovementComponent::moveBackward(float dt)
{
	SpatialComponent* spatialcomponent = this->GetSiblingComponent<SpatialComponent>();
	CameraComponent* cameraComponent = this->GetSiblingComponent<CameraComponent>();
	checkNeededComponents(spatialcomponent, cameraComponent);

	glm::vec3 pos = spatialcomponent->GetPosition();
	pos.x += (-strafeSpeed * cameraComponent->viewDirection * dt).x;
	pos.z += (-strafeSpeed * cameraComponent->viewDirection * dt).z;
	spatialcomponent->SetPosition(pos);
}

void MovementComponent::strafeLeft(float dt)
{
	SpatialComponent* spatialcomponent = this->GetSiblingComponent<SpatialComponent>();
	CameraComponent* cameraComponent = this->GetSiblingComponent<CameraComponent>();
	checkNeededComponents(spatialcomponent, cameraComponent);

	glm::vec3 strafeDirection = glm::cross(cameraComponent->viewDirection, Imgn::UP);

	glm::vec3 pos = spatialcomponent->GetPosition();
	pos.x += (-strafeSpeed * strafeDirection * dt).x;
	pos.z += (-strafeSpeed * strafeDirection * dt).z;
	spatialcomponent->SetPosition(pos);

}

void MovementComponent::strafeRight(float dt)
{
	SpatialComponent* spatialcomponent = this->GetSiblingComponent<SpatialComponent>();
	CameraComponent* cameraComponent = this->GetSiblingComponent<CameraComponent>();
	checkNeededComponents(spatialcomponent, cameraComponent);

	glm::vec3 strafeDirection = glm::cross(cameraComponent->viewDirection, Imgn::UP);

	glm::vec3 pos = spatialcomponent->GetPosition();
	pos.x += (strafeSpeed * strafeDirection * dt).x;
	pos.z += (strafeSpeed * strafeDirection * dt).z;
	spatialcomponent->SetPosition(pos);
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
	glm::vec3 pos = spatialcomponent->GetPosition();
	pos.y += (strafeSpeed * Imgn::UP * dt).y;
	spatialcomponent->SetPosition(pos);
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
	glm::vec3 pos = spatialcomponent->GetPosition();
	pos.y += (-strafeSpeed * Imgn::UP * dt).y;
	spatialcomponent->SetPosition(pos);

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

void MovementComponent::OnCollisionEnter(Imgn::Entity *)
{
	Imgn::RigidBody* rigidBody = GetSiblingComponent<Imgn::RigidBody>();
	rigidBody->AddForce(rigidBody->GetVelocity() * -2.0f * 120.f);
}

void MovementComponent::Update(float dt)
{
	static float m_dt = 0;
	m_dt += dt;
	Imgn::RigidBody* rigidBody = GetSiblingComponent<Imgn::RigidBody>();
	SpatialComponent* spatial = GetSiblingComponent<SpatialComponent>();
	if (rigidBody)
	{
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			rigidBody->AddForce(Imgn::Vector3(0, 0, -strafeSpeed));
		}
		else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			rigidBody->AddForce(Imgn::Vector3(0, 0, strafeSpeed));
		}
		else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			if (m_dt > .4)
			{
				spatial->SetPosition(spatial->GetPosition() + glm::vec3(-5, 0, 0));
				spatial->UpdatePosition();
				m_dt = 0;
			}
		}
		else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			if (m_dt > .4)
			{
				spatial->SetPosition(spatial->GetPosition() + glm::vec3(5, 0, 0));
				spatial->UpdatePosition();
				m_dt = 0;
			}
		}
	}
}
