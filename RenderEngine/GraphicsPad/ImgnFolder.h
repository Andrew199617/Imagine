#pragma once
#include "ImgnWidget.h"
#include "CBDirectory.h"
class CBFolderData;
class FolderButton;
class QVBoxLayout;
class QMenu;
struct dirent;

class ImgnFolder : public ImgnWidget
{
	Q_OBJECT
public:
	ImgnFolder(std::string name, std::string fileLocation = "../../StaticData");
	ImgnFolder(dirent * CurrentFolder, int FolderLevel, std::string fileLocation = "../../StaticData");
	~ImgnFolder();

	FolderButton* GetFolder() const { return folder; }
	//Used to find child folder that was pressed.
	void UnCheck(std::string objectName, CBFolderData* FolderData);
	//This folder was pressed but needs to uncheck all its children.
	void UnCheck();
	void ShowFolderData(CBFolderData* FolderData);
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

	bool showingFolderData;
};

