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
	static int i = 0;
	if (curFile == Imgn::MAX_FILES_ROW * i)
	{
		filesHolder->addLayout(filesLayout[i] = new QHBoxLayout, 0);
	}
	filesLayout[i]->addWidget(files[curFile] = new CBFile(Entry), 0, Qt::AlignLeft);
	curFile++;
	
}

void CBFolderData::Initialize()
{
	curFile = 0;
	filesHolder = new QVBoxLayout;
	filesHolder->setSpacing(0);
	filesHolder->setContentsMargins(0, 5, 0, 5);
	
	setLayout(filesHolder);

	sizePolicy().setHorizontalPolicy(QSizePolicy::Expanding);
	sizePolicy().setVerticalPolicy(QSizePolicy::Expanding);
	setObjectName("FolderData");
	filesHolder->setObjectName("FolderData");
}
