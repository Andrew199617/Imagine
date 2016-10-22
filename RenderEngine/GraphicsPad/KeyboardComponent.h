#pragma once
#include "ImgnComponent.h"
class MovementComponent;

class KeyboardComponent :
	public ImgnComponent
{
public:
	KeyboardComponent();
	~KeyboardComponent();

protected:
	bool Initialize() override;

public:
	void ProcessKeys(float m_dt);
	MovementComponent* movementComponent;
};

