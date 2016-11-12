#pragma once
#include "ImgnFrame.h"
class QBoxLayout;
class ImgnFolder;
class CBFolderData;

namespace Imgn
{
	enum
	{
		MAX_FOLDERS = 20
	};
}

class CBDirectory : public ImgnFrame
{
	Q_OBJECT
public:
	CBDirectory(std::string Location);
	CBDirectory();
	~CBDirectory();

	QBoxLayout* GetLayout() const { return m_Layout; }
	void SetCBFolderData(CBFolderData* FolderData);
protected:
	virtual void Initialize() override;
	void AddFolder();

private slots:
	void ShowFolderData(std::string objectName);

private:
	std::string location;
	QBoxLayout* m_Layout;
	ImgnFolder* folder;
	CBFolderData* folderData;

};

