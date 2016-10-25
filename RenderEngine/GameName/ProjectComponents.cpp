#pragma once
#include "test.h"
#include "..\GraphicsPad\DetailsLayout.h"
#include <windows.h>
#include "math.h"    
#define M_PI 3.14159

BOOL APIENTRY DllMain(
	HANDLE hModule,	   // Handle to DLL module 
	DWORD ul_reason_for_call,
	LPVOID lpReserved)     // Reserved
{

	cout << "hello" << endl;
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		// A process is loading the DLL.
		break;

	case DLL_THREAD_ATTACH:
		// A process is creating a new thread.
		break;

	case DLL_THREAD_DETACH:
		// A thread exits normally.
		break;

	case DLL_PROCESS_DETACH:
		// A process unloads the DLL.
		break;
	}
	return TRUE;
}

extern "C" __declspec(dllexport) void AddComponents();

__declspec(dllexport) void AddComponents()
{
	DetailsLayout::Instance()->CreateAction<Test>();
}