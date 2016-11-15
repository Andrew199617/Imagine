#pragma once
#include "ImgnFrame.h"
class QVBoxLayout;
class QHBoxLayout;
class CBFile;

namespace Imgn
{
	enum
	{
		MAX_FILES_ROW = 6,
		MAX_FILES_COLUMN = 3,
	};
}

class CBFolderData : public ImgnFrame
{

public:
	CBFolderData();
	~CBFolderData();

	void AddFile(struct dirent * Entry);
	int CurFile();
protected:
	virtual void Initialize() override;

private:
	QVBoxLayout* filesLayoutHolder;
	QHBoxLayout* filesLayout[Imgn::MAX_FILES_COLUMN];
	CBFile* files[Imgn::MAX_FILES_ROW * Imgn::MAX_FILES_COLUMN];

	int curFile;
public:
	void DeleteData();
private:
	int numLayouts; 
	struct dirent * entry;
};

