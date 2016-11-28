#pragma once
#include "ImgnComponent.h"
#include "DetailsLayout.h"
#include "ImgnProperties.h"

class Pickup :
	public ImgnComponent
{
	IMGN_GENERATE(Pickup)
	IMGN_PROPERTY(timeBeforeDelete, 1.0f)
	IMGN_END(Pickup)
public:
	float timeBeforeDelete;
};
