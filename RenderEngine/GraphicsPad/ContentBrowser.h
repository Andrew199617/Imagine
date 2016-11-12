#pragma once
#include "ImgnFrame.h"
class QVBoxLayout;
class QHBoxLayout;
class ImgnFolder;
class CBDirectory;
class CBFolderData;

class ContentBrowser :
	public ImgnFrame
{
public:
	ContentBrowser();
	~ContentBrowser();
protected:
	void Initialize() override;

private:
	QHBoxLayout* m_Layout;
	CBDirectory* directory;
	CBFolderData* folderData;

	std::string fileLocation;

};

