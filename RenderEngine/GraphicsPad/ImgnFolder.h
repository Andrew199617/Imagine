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

	FolderButton* GetFolder() const { return folderButton; }
	//Used to find child folder that was pressed.
	void UnCheck(std::string objectName, CBFolderData* FolderData);
	//This folder was pressed but needs to uncheck all its children.
	void UnCheckChildren(CBFolderData* FolderData);
	void UpdateFolderData(CBFolderData* FolderData);
	int GetFolderLevel() const { return folderLevel; }
	bool HasChildren();
	bool GetShowingFolderData() const { return showingFolderData; }

	std::string Location() const { return location; }
	void Location(std::string val) { location = val; }
	FolderButton* GetFolderButton() const { return folderButton; }
	void SetFolderButton(FolderButton* val) { folderButton = val; }
protected:
	void Initialize();
signals:
	void pressed(std::string objectName);

private slots:
	// Show Folder Data on left sided
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

	FolderButton* folderButton;
	QMenu* folderMenu;
	ImgnFolder* subFolders[Imgn::MAX_FOLDERS];

	static ImgnFolder* curFolderData;
	dirent* currentFolder;
	int curFolder;
	bool showingDirectory;
	bool hasChildren;

	bool showingFolderData;
};

