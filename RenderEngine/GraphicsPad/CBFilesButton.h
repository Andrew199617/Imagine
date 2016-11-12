#pragma once
#include "FolderButton.h"
struct dirent;

class CBFilesButton : public FolderButton
{
public:
	CBFilesButton(dirent* Entry);
	~CBFilesButton();

protected:
	void Initialize();

private:
	dirent* entry;
	std::string fileType;
	void GetFileExtension();

};

