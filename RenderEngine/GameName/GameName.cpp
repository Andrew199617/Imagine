// GameName.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Test.h"

Test* test = new Test();

extern "C" ImgnComponent* AddActionToDetailsLayout(string* s);

extern "C" ImgnComponent* AddActionToDetailsLayout(string* s)
{
	*s = typeid(Test).name();
	return test;
}