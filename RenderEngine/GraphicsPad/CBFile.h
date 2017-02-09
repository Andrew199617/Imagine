#pragma once
#include "ImgnWidget.h"
class QLabel;
class QVBoxLayout;
class CBFilesButton;
struct dirent;

class CBFile : public ImgnWidget
{
public:
	CBFile();
	CBFile(dirent* Entry,std::string FilePath);
	~CBFile();

protected:
	virtual void Initialize() override;

private:
	QVBoxLayout* m_layout;
	std::string name;
	std::string filePath;

	CBFilesButton* button;
	QLabel* fileNameLabel;
	dirent* entry;

};

