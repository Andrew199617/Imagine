#pragma once
#include "ImgnFrame.h"
class QVBoxLayout;
class QHBoxLayout;
class CBFile;
class QScrollArea;

namespace Imgn
{
	enum
	{
		MAX_FILES_ROW = 7,
		MAX_FILES_COLUMN = 4,
	};
}

class CBFolderData : public QWidget
{

public:
	CBFolderData(QWidget* parent);
	~CBFolderData();

	void AddFile(struct dirent * Entry, std::string filePath);
	int CurFile();
protected:
	virtual void Initialize();

private:
	QVBoxLayout* filesLayoutHolder;
	QHBoxLayout* filesLayout[Imgn::MAX_FILES_COLUMN];
	CBFile* files[Imgn::MAX_FILES_ROW * Imgn::MAX_FILES_COLUMN];
	QScrollArea* scrollArea;

	int curFile;
public:
	void DeleteData();
private:
	int numLayouts; 
	struct dirent * entry;
};

