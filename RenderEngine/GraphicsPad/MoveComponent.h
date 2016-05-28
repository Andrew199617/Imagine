#pragma once
#include "Component.h"
class MoveComponent :
	public Component
{
public:
	MoveComponent();
	~MoveComponent();

	virtual bool Update(float dt) override;

};

