#pragma once
#include "ImgnComponent.h"
class MoveComponent :
	public ImgnComponent
{
public:
	MoveComponent();
	~MoveComponent();

	virtual bool Update(float dt) override;

};

