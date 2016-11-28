#pragma once
#include "ImgnComponent.h"
#include "DetailsLayout.h"
#include "ImgnProperties.h"

class Pickup :
	public ImgnComponent
{
	IMGN_GENERATE(Pickup)
	\\Use IMGN_PROPERTY(var_name) to have variable appear in editor
	\\IMGN_PROPERTY(gravity, 9.8)
	\\...
	IMGN_END(Pickup)
public:
};
