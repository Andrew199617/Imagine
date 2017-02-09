#pragma once
#include "ImgnFrame.h"
class QVBoxLayout;
class QHBoxLayout;
class ImgnFolder;
class CBDirectory;
class CBFolderData;
class CBFolderDataHolder;

class ContentBrowser :
	public ImgnFrame
{
public:
	ContentBrowser();
	~ContentBrowser();

	void SetHidden(bool);

	bool IsHidden() const { return isHidden; }
	void SetIsHidden(bool val) { isHidden = val; }
protected:
	void Initialize() override;

private:
	QHBoxLayout* m_Layout;
	CBDirectory* directory;
	CBFolderDataHolder* folderDataHolder;

	std::string fileLocation;
	bool isHidden;

};

