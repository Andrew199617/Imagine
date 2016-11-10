#include "CBDirectory.h"
#include "Qt/qboxlayout.h"
#include "dirent.h"
#include "ImgnFolder.h"
#include "FolderButton.h"


CBDirectory::CBDirectory()
{
	location = "";
	Initialize();
}


CBDirectory::CBDirectory(std::string Location)
{
	location = Location;
	Initialize();
}

CBDirectory::~CBDirectory()
{
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
		GetDirectory();
	}
}

void CBDirectory::GetDirectory()
{
	curFolder = 0;
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

void CBDirectory::AddFolder(struct dirent * entry)
{
	folders[curFolder] = new ImgnFolder(entry, 0,location + "/" + entry->d_name);
	connect(folders[curFolder],SIGNAL(pressed(std::string)), this, SLOT(ShowFolderData(std::string)));
	m_Layout->addWidget(folders[curFolder], 0, Qt::AlignLeft);

	curFolder++;
}

void CBDirectory::ShowFolderData(std::string objectName)
{

	for (int i = 0; i < curFolder; ++i)
	{
		if (folders[i]->objectName() != objectName.c_str())
		{
			folders[i]->UnCheck(objectName);
		}
		else
		{
			folders[i]->ShowFolderData();
			if (folders[i]->HasChildren())
			{
				folders[i]->UnCheck();
			}
		}
	}
}
