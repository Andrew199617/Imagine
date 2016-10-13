#pragma once
#include "Component.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm.hpp>
#pragma warning(pop)
#include "CameraComponent.h"
#pragma warning(push)
#pragma warning (disable:4127)
#include <QtGui\qkeyevent>
#pragma warning(pop)

class MouseComponent :
	public Component
{
	glm::vec2 newMousePosition;
	glm::vec2 oldMousePosition;
	glm::vec2 mouseDelta;
public:
	MouseComponent();
	~MouseComponent();

public:
	glm::vec2 GetMouseDelta() { return mouseDelta; }
	void setNewMousePosition(glm::vec2 newMousePos) { newMousePosition = newMousePos; }
	void setOldMousePosition() { oldMousePosition = newMousePosition; }
	void setMouseDelta();
	void ProcessMouseMove(QMouseEvent* e);
};

