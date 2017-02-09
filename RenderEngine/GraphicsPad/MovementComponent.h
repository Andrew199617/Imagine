#pragma once
#include "ImgnComponent.h"
#include "SpatialComponent.h"
#include "CameraComponent.h"
#include "ImgnProperties.h"

class MovementComponent :
	public ImgnComponent
{
	IMGN_GENERATE(MovementComponent)
	IMGN_PROPERTY(strafeSpeed,0.0f)
	IMGN_END(MovementComponent)
	
protected:
	virtual bool Initialize() override;

public:
	void checkNeededComponents(ImgnComponent* spatial, ImgnComponent* camera);
	void moveForward(float dt);
	void moveForward(float dt, glm::vec3 viewDirection);
	void moveBackward(float dt);
	void strafeLeft(float dt);
	void strafeRight(float dt);
	void moveUp(float dt);
	void moveDown(float dt);
	void Jump(int time, float dt);

	void OnCollisionEnter(Imgn::Entity*);
	virtual void Update(float dt) override;

public:
	void SetStrafeSpeed(float Speed) { strafeSpeed = Speed; }
	float GetStrafeSpeed() { return strafeSpeed; }

private:
	float strafeSpeed;
};

