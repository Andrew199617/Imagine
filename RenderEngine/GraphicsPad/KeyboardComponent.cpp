#include "KeyboardComponent.h"
#include "SpatialComponent.h"
#include "CameraComponent.h"
#include "GravityComponent.h"
#include "MovementComponent.h"
#include "ShootingComponent.h"

KeyboardComponent::KeyboardComponent()
{
	
}

KeyboardComponent::~KeyboardComponent()
{
}

void KeyboardComponent::ProcessKeys(float m_dt)
{
	static float dt = 0;
	dt += m_dt;
	MovementComponent* movementComponent = this->GetSiblingComponent<MovementComponent>();
	if (!movementComponent)
	{
		string s = ": can not obtain Movement Component";
		GameLogger::log(this->GetName() + s);
		GameLogger::shutdownLog();
		exit(1);
	}
	if (GetAsyncKeyState(Qt::Key::Key_W) != 0)
	{
		movementComponent->moveForward(m_dt);
	}
	if (GetAsyncKeyState(Qt::Key::Key_S) != 0)
	{
		movementComponent->moveBackward(m_dt);
	}
	if (GetAsyncKeyState(Qt::Key::Key_A) != 0)
	{
		movementComponent->strafeLeft(m_dt);
	}
	if (GetAsyncKeyState(Qt::Key::Key_D) != 0)
	{
		movementComponent->strafeRight(m_dt);
	}
	if (GetAsyncKeyState(Qt::Key::Key_R) != 0)
	{
		movementComponent->moveUp(m_dt);
	}
	if (GetAsyncKeyState(Qt::Key::Key_F) != 0)
	{
		movementComponent->moveDown(m_dt);
	}
	if (GetAsyncKeyState(Qt::Key::Key_O) != 0)
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
	if (GetAsyncKeyState(Qt::Key::Key_B) != 0 && dt > .5)
	{
		VertexShaderInfo::isBumped = !VertexShaderInfo::isBumped;
		dt = 0;
	}
}


