#pragma once
#include "ImgnComponent.h"
#include "DetailsLayout.h"
#include "ImgnProperties.h"

class Pickup :
	public ImgnComponent
{
	IMGN_GENERATE(Pickup)
	IMGN_PROPERTY(rotationSpeed, 2)
	IMGN_END(Pickup)
public:
	float rotationSpeed;
	int Score;

	virtual void Update(float) override;


};
