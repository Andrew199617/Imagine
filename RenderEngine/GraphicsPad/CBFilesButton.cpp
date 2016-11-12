#include "CBFilesButton.h"
#include "dirent.h"
#include "Qt\qdir.h"

CBFilesButton::CBFilesButton(dirent * Entry) : FolderButton(false)
{
	fileType = "";
	entry = Entry;
	Initialize();
}

CBFilesButton::~CBFilesButton()
{
	
}

void CBFilesButton::Initialize()
{
	QPixmap pixmap;
	QIcon icon;
	if (entry->d_type == DT_DIR)
	{
		//Is Folder
		pixmap.load("../EngineData/Icons/Folder.png");
		icon.addPixmap(pixmap);
	}
	else if (entry->d_type == DT_REG)
	{
		GetFileExtension();
		if (fileType == "txt")
		{
			pixmap.load("../EngineData/Icons/Txt.png");
			icon.addPixmap(pixmap);
		}
		else if (fileType == "imgnasset")
		{
			pixmap.load("../EngineData/Icons/ImgnAsset.png");
			icon.addPixmap(pixmap);
		}
	}
	else
	{
		setText("No Icon");
	}

	setIcon(icon);
	setIconSize(QSize(48, 48));
	setObjectName("FilesButton");
	setFixedSize(48, 48);
	sizePolicy().setHorizontalPolicy(QSizePolicy::Expanding);
}

void CBFilesButton::GetFileExtension()
{
	char* cFileType = 0;
	for (unsigned i = 0; i < entry->d_namlen; ++i)
	{	
		if (entry->d_name[i] == '.')
		{
			i++;
			cFileType = new char[entry->d_namlen - i + 1];
			strcpy_s(cFileType, entry->d_namlen - i + 1, entry->d_name + i);
		}
	}
	if (cFileType)
	{
		fileType = cFileType;
		delete cFileType;
	}
}
