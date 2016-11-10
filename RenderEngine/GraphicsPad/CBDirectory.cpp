#include "CBDirectory.h"
#include "Qt/qboxlayout.h"
#include "dirent.h"
#include "ImgnFolder.h"


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

int CBDirectory::isDirectory(const char *path) {
	struct stat statbuf;
	if (stat(path, &statbuf) != 0)
		return 0;
	return S_ISDIR(statbuf.st_mode);
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
	m_Layout->addWidget(folders[curFolder], 0, Qt::AlignLeft);

	curFolder++;
}
