#pragma once
#include "ImgnComponent.h"
#include "ImgnProperties.h"

class Test :
	public ImgnComponent
{
	IMGN_GENERATE(Test)
	IMGN_PROPERTY(DllVar, 0)
	IMGN_PROPERTY(DllVar, 0)
	IMGN_END(Test)
public:
	int DllVar;
	virtual bool Update(float) override;

};

