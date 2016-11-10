#pragma once
#include "ImgnWidget.h"
#include "CBDirectory.h"
class FolderButton;
class QVBoxLayout;
class QMenu;
struct dirent;

class ImgnFolder : public ImgnWidget
{
	Q_OBJECT
public:
	ImgnFolder(dirent * CurrentFolder, int FolderLevel, std::string fileLocation = "../../StaticData");
	~ImgnFolder();

	FolderButton* GetFolder() const { return folder; }
	//If you don't want to check a specific child
	void UnCheck(std::string objectName);
	//if you don't want to uncheck this folder but want to uncheck its children.
	void UnCheck();
	void ShowFolderData();
	int GetFolderLevel() const { return folderLevel; }
	bool HasChildren();
protected:
	void Initialize();
signals:
	void pressed(std::string objectName);

private slots:
	void UpdateDirectory();
	//capture buttons pressed
	void Pressed();
	//capture folders pressed
	void Pressed(std::string objectName);

private:
	void AddFolder(struct dirent * entry);
	void HideDirectory();
	void ShowDirectory();

private:
	std::string location;
	QVBoxLayout* m_Layout;
	int folderLevel;

	FolderButton* folder;
	QMenu* folderMenu;
	ImgnFolder* subFolders[Imgn::MAX_FOLDERS];

	dirent* currentFolder;
	int curFolder;
	bool showingDirectory;
	bool hasChildren;

};

