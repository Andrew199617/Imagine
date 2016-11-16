#pragma once
#include <Windows.h>
#include <Commdlg.h>
#include <tchar.h>
#include <string>

using namespace std;

class OpenFileDialog
{
public:
	OpenFileDialog(void);
	string GetFile();
	string GetExtension(string filePath);

	TCHAR*DefaultExtension;
	TCHAR*FileName;
	TCHAR*Filter;
	int FilterIndex;
	int Flags;
	TCHAR*InitialDir;
	HWND Owner;
	TCHAR*Title;

	bool ShowDialog();
};