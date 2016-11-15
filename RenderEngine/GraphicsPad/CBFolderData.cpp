#include "CBFolderData.h"
#include "Qt\qboxlayout.h"
#include "CBFilesButton.h"
#include "dirent.h"
#include "CBFile.h"

CBFolderData::CBFolderData()
{
	Initialize();
}


CBFolderData::~CBFolderData()
{
}

void CBFolderData::AddFile(struct dirent * Entry)
{
	if (curFile == Imgn::MAX_FILES_ROW * numLayouts)
	{
		filesLayoutHolder->addLayout(filesLayout[numLayouts] = new QHBoxLayout, 0);
		filesLayout[numLayouts]->setSpacing(0);
		filesLayout[numLayouts]->setContentsMargins(0, 0, 0, 0);
		numLayouts++;
	}
	filesLayout[numLayouts-1]->addWidget(files[curFile] = new CBFile(Entry), 0, Qt::AlignLeft);
	curFile++;
}

int CBFolderData::CurFile()
{
	return curFile;
}

void CBFolderData::Initialize()
{
	numLayouts = 0;
	curFile = 0;
	filesLayoutHolder = new QVBoxLayout;
	filesLayoutHolder->setSpacing(0);
	filesLayoutHolder->setContentsMargins(0, 0, 0, 0);
	
	setLayout(filesLayoutHolder);

	sizePolicy().setHorizontalPolicy(QSizePolicy::Expanding);
	sizePolicy().setVerticalPolicy(QSizePolicy::Expanding);
	setObjectName("FolderData");
	filesLayoutHolder->setObjectName("FolderData");
}

void CBFolderData::DeleteData()
{
	for (int i = 0; i < numLayouts;++i)
	{
		for (int j = i * Imgn::MAX_FILES_ROW; j < curFile && j < (i+1) * Imgn::MAX_FILES_ROW; ++j)
		{
			filesLayout[i]->removeWidget(files[j]);
			delete files[j];
		}
	}
	numLayouts = 0;
	curFile = 0;
}
