#include "ImgnFolder.h"
#include "Qt\qboxlayout.h"
#include "Qt\qpushbutton.h"
#include "dirent.h"
#include "Qt/qsizepolicy.h"
#include "ImgnButton.h"
#include "FolderButton.h"
#include "CBFolderData.h"

ImgnFolder* ImgnFolder::curFolderData = 0;

ImgnFolder::ImgnFolder(dirent * CurrentFolder, int FolderLevel, std::string fileLocation)
{
	folderLevel = FolderLevel;
	location = fileLocation;
	currentFolder = CurrentFolder;
	setObjectName(currentFolder->d_name);
	Initialize();
}


ImgnFolder::ImgnFolder(std::string name, std::string fileLocation)
{
	location = fileLocation;
	folderLevel = 0;
	setObjectName(name.c_str());
	Initialize();
}

ImgnFolder::~ImgnFolder()
{

}

void ImgnFolder::Initialize()
{
	showingFolderData = false;
	showingDirectory = false;
	hasChildren = 0;
	curFolder = 0;
	m_Layout = new QVBoxLayout;

	m_Layout->setSpacing(0);
	m_Layout->setContentsMargins(0, 0, 0, 0);
	this->setLayout(m_Layout);

	m_Layout->addWidget(folderButton = new FolderButton, 0, Qt::AlignTop);
	folderButton->setObjectName(objectName());
	folderButton->setText(objectName());
	connect(folderButton, SIGNAL(DoubleClicked()), this, SLOT(UpdateDirectory()));
	connect(folderButton, SIGNAL(pressed()), this, SLOT(Pressed()));

	setMinimumWidth(300);
	sizePolicy().setHorizontalPolicy(QSizePolicy::Policy::Expanding);							
	sizePolicy().setVerticalPolicy(QSizePolicy::Policy::Minimum);

	std::string str = std::to_string(folderLevel * 25 + 20) + ";}";
	std::string menuIndicatorStyle = "QPushButton::menu-indicator { left: " + std::to_string(folderLevel * 25 + 5) + ";}";
	folderButton->setStyleSheet(folderButton->styleSheet() + ("QPushButton { padding-left: " + str + menuIndicatorStyle).c_str());
	
	UpdateDirectory();
}

void ImgnFolder::UpdateDirectory()
{
	if (!showingDirectory)
	{
		ShowDirectory();
		folderButton->SetCheckedMenu(true);
	}
	else
	{
		HideDirectory();
		folderButton->SetCheckedMenu(false);
	}
	showingDirectory = !showingDirectory;
}

void ImgnFolder::ShowDirectory()
{
	
	if (curFolder == 0)
	{
		DIR *pDIR;
		struct dirent *entry;
		if (pDIR = opendir(location.c_str()))
		{
			while (entry = readdir(pDIR))
			{
				if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
				{
					if (entry->d_type == DT_DIR)
					{
						AddFolder(entry);
					}
				}
			}
			closedir(pDIR);
		}
	}
	else
	{
		for (int i = 0; i < curFolder; ++i)
		{
			subFolders[i]->setVisible(true);
		}
	}
}


void ImgnFolder::Pressed()
{
	QObject* sender = QObject::sender();
	std::string objectName = sender->objectName().toLocal8Bit().constData();
	emit pressed(objectName);
}

void ImgnFolder::Pressed(std::string objectName)
{
	emit pressed(objectName);
}

void ImgnFolder::UnCheck(std::string objectName, CBFolderData* FolderData)
{
	if (folderButton->isChecked())
	{
		folderButton->setChecked(false);
		UpdateFolderData(FolderData);
	}
	int folderDataToShow = -1;
	for (int i = 0; i < curFolder; ++i)
	{
		if (subFolders[i]->objectName() != objectName.c_str())
		{
			subFolders[i]->UnCheck(objectName, FolderData);
		}
		else
		{
			folderDataToShow = i;
		}
	}
	if (folderDataToShow != -1)
	{
		
		subFolders[folderDataToShow]->UnCheckChildren(FolderData);
		if (!subFolders[folderDataToShow]->showingFolderData)
		{
			subFolders[folderDataToShow]->UpdateFolderData(FolderData);
		}
	}
}

void ImgnFolder::UnCheckChildren(CBFolderData* FolderData)
{
	if (!HasChildren())
	{
		return;
	}
	for (int i = 0; i < curFolder; ++i)
	{
		if (subFolders[i]->GetFolder()->isChecked())
		{
			subFolders[i]->GetFolder()->setChecked(false);
			subFolders[i]->UpdateFolderData(FolderData);
		}
		subFolders[i]->UnCheckChildren(FolderData);
	}
}

void ImgnFolder::HideDirectory()
{
	for (int i = 0; i < curFolder; ++i)
	{
		subFolders[i]->setVisible(false);
	}
}

void ImgnFolder::UpdateFolderData(CBFolderData* FolderData)
{	
	if (!showingFolderData)
	{
		if (FolderData->CurFile() != 0)
		{
			curFolderData = this;
			return;
		}
		DIR *pDIR;
		struct dirent *entry;
		if (pDIR = opendir(location.c_str()))
		{
			while (entry = readdir(pDIR))
			{
				if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
				{
					FolderData->AddFile(entry,location.c_str());
				}
			}
			closedir(pDIR);
		}
		showingFolderData = true;
		curFolderData = 0;
	}
	else if(!folderButton->isChecked())
	{
		FolderData->DeleteData();
		if (curFolderData)
		{
			curFolderData->UpdateFolderData(FolderData);
		}
		showingFolderData = false;
	}
}

bool ImgnFolder::HasChildren()
{
	return hasChildren;
}

void ImgnFolder::AddFolder(struct dirent * entry)
{
	subFolders[curFolder] = new ImgnFolder(entry, folderLevel + 1 , location + "/" + entry->d_name);
	connect(subFolders[curFolder], SIGNAL(pressed(std::string)), this, SLOT(Pressed(std::string)));
	m_Layout->addWidget(subFolders[curFolder], 0, Qt::AlignTop);

	hasChildren = true;
	curFolder++;
}

