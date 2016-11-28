// GameName.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Pickup.h"

Pickup* test = new Pickup();

extern "C" ImgnComponent* AddActionToDetailsLayout(string* s);

extern "C" ImgnComponent* AddActionToDetailsLayout(string* s)
{
	*s = typeid(Pickup).name();
	return test;
}