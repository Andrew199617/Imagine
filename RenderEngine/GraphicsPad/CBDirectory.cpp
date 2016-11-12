#include "CBDirectory.h"
#include "Qt/qboxlayout.h"
#include "dirent.h"
#include "ImgnFolder.h"
#include "FolderButton.h"

CBDirectory::CBDirectory(std::string Location)
{
	location = Location;
	Initialize();
}

CBDirectory::~CBDirectory()
{
}

void CBDirectory::SetCBFolderData(CBFolderData* FolderData)
{
	folderData = FolderData;
}

void CBDirectory::Initialize()
{
	m_Layout = new QVBoxLayout;
	m_Layout->setSpacing(0);
	m_Layout->setContentsMargins(0, 0, 0, 0);

	this->setObjectName("Directory");
	this->setLayout(m_Layout);

	if (location != "")
	{
		AddFolder();
	}
}

void CBDirectory::AddFolder()
{
	folder = new ImgnFolder("StaticData",location);
	connect(folder,SIGNAL(pressed(std::string)), this, SLOT(ShowFolderData(std::string)));
	m_Layout->addWidget(folder,0,Qt::AlignTop);

}

void CBDirectory::ShowFolderData(std::string objectName)
{
	if (folder->objectName() != objectName.c_str())
	{
		folder->UnCheck(objectName,folderData);
	}
	else
	{
		folder->ShowFolderData(folderData);
		if (folder->HasChildren())
		{
			folder->UnCheck();
		}
	}
}
