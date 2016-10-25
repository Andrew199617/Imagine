#pragma once
#include "..\GraphicsPad\ImgnComponent.h"
#include "..\GraphicsPad\ImgnComponent.cpp"
#include "..\GraphicsPad\Component.h"
#include "..\GraphicsPad\Component.cpp"
#include "..\GraphicsPad\GameLogger.h"
#include "..\GraphicsPad\GameLogger.cpp"
#include "..\GraphicsPad\ImgnProperties.h"
#include "..\GraphicsPad\ImgnProperties.cpp"

class Test :
	public ImgnComponent
{
	IMGN_GENERATE(Test)
	IMGN_PROPERTY(hello,0)
	IMGN_END(Test)
public:
	int hello;
};

