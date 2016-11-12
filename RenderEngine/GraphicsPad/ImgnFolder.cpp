#include "ImgnFolder.h"
#include "Qt\qboxlayout.h"
#include "Qt\qpushbutton.h"
#include "dirent.h"
#include "Qt/qsizepolicy.h"
#include "ImgnButton.h"
#include "FolderButton.h"
#include "CBFolderData.h"

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
	showingFolderData = 0;
	showingDirectory = 0;
	hasChildren = 0;
	curFolder = 0;
	m_Layout = new QVBoxLayout;

	m_Layout->setSpacing(0);
	m_Layout->setContentsMargins(0, 0, 0, 0);
	this->setLayout(m_Layout);

	m_Layout->addWidget(folder = new FolderButton, 0, Qt::AlignTop);
	folder->setObjectName(objectName());
	folder->setText(objectName());
	connect(folder, SIGNAL(DoubleClicked()), this, SLOT(UpdateDirectory()));
	connect(folder, SIGNAL(pressed()), this, SLOT(Pressed()));

	setMinimumWidth(300);
	sizePolicy().setHorizontalPolicy(QSizePolicy::Policy::Expanding);							
	sizePolicy().setVerticalPolicy(QSizePolicy::Policy::Minimum);

	std::string str = std::to_string(folderLevel * 25 + 20) + ";}";
	std::string menuIndicatorStyle = "QPushButton::menu-indicator { left: " + std::to_string(folderLevel * 25 + 5) + ";}";
	folder->setStyleSheet(folder->styleSheet() + ("QPushButton { padding-left: " + str + menuIndicatorStyle).c_str());
	
}

void ImgnFolder::UpdateDirectory()
{
	if (!showingDirectory)
	{
		ShowDirectory();
		folder->SetCheckedMenu(true);
	}
	else
	{
		HideDirectory();
		folder->SetCheckedMenu(false);
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
		/*for (int i = 0; i < curFolder; ++i)
		{
			subFolders[i]->setVisible(true);
		}*/
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
	folder->setChecked(false);
	for (int i = 0; i < curFolder; ++i)
	{
		if (subFolders[i]->objectName() != objectName.c_str())
		{
			subFolders[i]->UnCheck(objectName, FolderData);
		}
		else
		{
			subFolders[i]->ShowFolderData(FolderData);
			if (subFolders[i]->HasChildren())
			{
				subFolders[i]->UnCheck();
			}
		}
	}
}

void ImgnFolder::UnCheck()
{
	for (int i = 0; i < curFolder; ++i)
	{
		subFolders[i]->GetFolder()->setChecked(false);
		if (subFolders[i]->HasChildren())
		{
			subFolders[i]->UnCheck();
		}
	}
}

void ImgnFolder::HideDirectory()
{
	for (int i = 0; i < curFolder; ++i)
	{
		subFolders[i]->setVisible(false);
	}
}

void ImgnFolder::ShowFolderData(CBFolderData* FolderData)
{	
	if (!showingFolderData)
	{
		DIR *pDIR;
		struct dirent *entry;
		if (pDIR = opendir(location.c_str()))
		{
			while (entry = readdir(pDIR))
			{
				if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
				{
					FolderData->AddFile(entry);
				}
			}
			closedir(pDIR);
		}
	}
	showingFolderData = true;
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

