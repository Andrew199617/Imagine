#include "KeyboardComponent.h"
#include "SpatialComponent.h"
#include "CameraComponent.h"
#include "GravityComponent.h"
#include "MovementComponent.h"
#include "ShootingComponent.h"
#include "RenderEngine\VertexShaderInfo.h"
#include <Windows.h>
#include "glm.hpp"

KeyboardComponent::KeyboardComponent()
{
	
}

KeyboardComponent::~KeyboardComponent()
{
}

bool KeyboardComponent::Initialize()
{
	movementComponent = this->GetSiblingComponent<MovementComponent>();
	if (!movementComponent)
	{
		string s = ": can not obtain Movement Component";
		GameLogger::log(this->GetName() + s);
		GameLogger::shutdownLog();
		exit(1);
	}
	return true;
}

void KeyboardComponent::ProcessKeys(float m_dt)
{
	static float dt = 0;
	dt += m_dt;
	
	if (GetAsyncKeyState(Qt::Key::Key_W) & 0x8000)
	{
		movementComponent->moveForward(m_dt);
	}
	if (GetAsyncKeyState(Qt::Key::Key_S) & 0x8000)
	{
		movementComponent->moveBackward(m_dt);
	}
	if (GetAsyncKeyState(Qt::Key::Key_A) & 0x8000)
	{
		movementComponent->strafeLeft(m_dt);
	}
	if (GetAsyncKeyState(Qt::Key::Key_D) & 0x8000)
	{
		movementComponent->strafeRight(m_dt);
	}
	if (GetAsyncKeyState(Qt::Key::Key_R) & 0x8000)
	{
		movementComponent->moveUp(m_dt);
	}
	if (GetAsyncKeyState(Qt::Key::Key_F) & 0x8000)
	{
		movementComponent->moveDown(m_dt);
	}
	if (GetAsyncKeyState(Qt::Key::Key_O) & 0x8000)
	{
		ShootingComponent* shoot = this->GetSiblingComponent<ShootingComponent>();
		if (!shoot)
		{
			string s = ": can not obtain Shooting Component";
			GameLogger::log(this->GetName() + s);
			GameLogger::shutdownLog();
			exit(1);
		}
		shoot->Enable();
		shoot->viewDirection = this->GetSiblingComponent<CameraComponent>()->viewDirection;

	}
}


