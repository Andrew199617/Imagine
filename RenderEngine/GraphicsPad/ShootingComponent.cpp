#include "ShootingComponent.h"
#include "CameraComponent.h"
#include "Throwables.h"
#include "MovementComponent.h"

ShootingComponent::ShootingComponent()
{
	
}


ShootingComponent::~ShootingComponent()
{
}

bool ShootingComponent::Initialize()
{
	arrowHasntBeenShot = false;
	return true;
}

bool ShootingComponent::Update(float dt)
{
	CameraComponent* camera = this->GetSiblingComponent<CameraComponent>();
	if (!camera)
	{
		string s = ": can not obtain Camera Component";
		GameLogger::log(this->GetName() + s);
		GameLogger::shutdownLog();
		exit(1);
	}
	
	
	if (Throwables::ArrowSpatial.position.y >= 4)
	{
		Throwables::ArrowMove.moveForward(dt, viewDirection);
	}
	else
	{
		Disable();
	}
	
	return true;
}
