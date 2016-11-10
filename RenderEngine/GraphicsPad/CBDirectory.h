#pragma once
#include "ImgnFrame.h"
class QVBoxLayout;
class ImgnFolder;

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

	QVBoxLayout* GetLayout() const { return m_Layout; }
protected:
	virtual void Initialize() override;

	void GetDirectory();
	void AddFolder(struct dirent * entry);

private slots:
	void ShowFolderData(std::string objectName);

private:
	std::string location;
	QVBoxLayout* m_Layout;
	ImgnFolder* folders[Imgn::MAX_FOLDERS];
	int curFolder;

};

