#include "ObjController.h"
#include <Windows.h>
#define Q 81
#define W 87
#define R 82

ObjController::ObjController()
{
}


ObjController::~ObjController()
{
}

void ObjController::Update()
{
	if (GetAsyncKeyState(Q) != 0)
	{
		curType = Move;
	}
	else if (GetAsyncKeyState(W) != 0)
	{
		curType = Scale;
	}
	else if (GetAsyncKeyState(R) != 0)
	{
		curType = Rotate;
	}

	if ((GetKeyState(VK_LBUTTON) & 0x100) != 0) 
	{

	}
}
