#include "ImgnFolder.h"
#include "Qt\qboxlayout.h"
#include "Qt\qpushbutton.h"
#include "dirent.h"
#include "Qt/qsizepolicy.h"

ImgnFolder::ImgnFolder(dirent * CurrentFolder, int FolderLevel, std::string fileLocation)
{
	folderLevel = FolderLevel;
	location = fileLocation;
	currentFolder = CurrentFolder;
	setObjectName(currentFolder->d_name);
	Initialize();
}


ImgnFolder::~ImgnFolder()
{

}

void ImgnFolder::Initialize()
{
	m_Layout = new QVBoxLayout;
	m_Layout->setSpacing(0);
	m_Layout->setContentsMargins(0, 0, 0, 0);
	this->setLayout(m_Layout);
	m_Layout->addWidget(folder = new QPushButton, 0, Qt::AlignTop);
	setMaximumWidth(200);
	sizePolicy().setHorizontalPolicy(QSizePolicy::Policy::Expanding);							\
	sizePolicy().setVerticalPolicy(QSizePolicy::Policy::Minimum);
	folder->setText(objectName());

	setContentsMargins(folderLevel * 25, 0, 0, 0);
}

int ImgnFolder::isDirectory(const char *path) {
	struct stat statbuf;
	if (stat(path, &statbuf) != 0)
		return 0;
	return S_ISDIR(statbuf.st_mode);
}

void ImgnFolder::ShowDirectory()
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

void ImgnFolder::AddFolder(struct dirent * entry)
{
	subFolders[curFolder] = new ImgnFolder(entry, folderLevel + 1 , location + "/" + entry->d_name);
	m_Layout->addWidget(subFolders[curFolder], 0, Qt::AlignLeft);

	curFolder++;
}

