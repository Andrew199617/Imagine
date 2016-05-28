#include "MouseComponent.h"
#include "ShootingComponent.h"
#include "CameraComponent.h"

MouseComponent::MouseComponent()
{
}


MouseComponent::~MouseComponent()
{
}

void MouseComponent::setMouseDelta()
{
	CameraComponent* camera = this->GetSiblingComponent<CameraComponent>();
	mouseDelta = newMousePosition - oldMousePosition;
	if (!camera)
	{
		string s = ": can not obtain Camera Component";
		GameLogger::log(this->GetName() + s);
		GameLogger::shutdownLog();
		exit(1);
	}
	
	camera->mouseUpdate();
}

void MouseComponent::ProcessMouse(QMouseEvent* e)
{
	if (e->buttons() & Qt::LeftButton)
	{
		setNewMousePosition(glm::vec2(e->x(), e->y()));
		setMouseDelta();
	}
}