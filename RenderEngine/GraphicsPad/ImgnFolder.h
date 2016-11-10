#pragma once
#include "ImgnWidget.h"
#include "CBDirectory.h"
class QPushButton;
class QVBoxLayout;
class QMenu;
struct dirent;

class ImgnFolder : public ImgnWidget
{
	Q_OBJECT
public:
	ImgnFolder(dirent * CurrentFolder, int FolderLevel, std::string fileLocation = "../../StaticData");
	~ImgnFolder();
protected:
	void Initialize();

	int isDirectory(const char *path);
	void ShowDirectory();
	void AddFolder(struct dirent * entry);

	virtual void mouseDoubleClickEvent(QMouseEvent *) override;

private:
	std::string location;
	QVBoxLayout* m_Layout;
	int folderLevel;

	QPushButton* folder;
	QMenu* folderMenu;
	ImgnFolder* subFolders[Imgn::MAX_FOLDERS];
	dirent* currentFolder;
	int curFolder;
};

