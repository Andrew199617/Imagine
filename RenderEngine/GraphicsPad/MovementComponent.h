#pragma once
#include "Component.h"
#include "SpatialComponent.h"
#include "CameraComponent.h"

class MovementComponent :
	public Component
{

	float strafeSpeed;
public:
	MovementComponent(float Speed = 0.0f);
	~MovementComponent();
	virtual bool Initialize() override;

public:
	void checkNeededComponents(SpatialComponent* spatial, CameraComponent* camera);
	void moveForward(float dt);
	void moveForward(float dt, glm::vec3 viewDirection);
	void moveBackward(float dt);
	void strafeLeft(float dt);
	void strafeRight(float dt);
	void moveUp(float dt);
	void moveDown(float dt);
	void Jump(int time, float dt);
};

