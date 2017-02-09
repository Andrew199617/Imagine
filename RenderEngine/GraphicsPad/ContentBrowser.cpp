#include "ContentBrowser.h"
#include "dirent.h"
#include <string.h>
#include <iostream>
#include "ImgnFolder.h"
#include "Qt\qboxlayout.h"
#include "Qt\qpushbutton.h"
#include "CBDirectory.h"
#include "CBFolderData.h"
#include "CBFolderDataHolder.h"


ContentBrowser::ContentBrowser() : ImgnFrame()
{
	Initialize();
}


ContentBrowser::~ContentBrowser()
{
}

void ContentBrowser::SetHidden(bool b)
{
	isHidden = b;
	this->setHidden(b);
	directory->setHidden(b);
}

void ContentBrowser::Initialize()
{
	isHidden = false;

	this->setObjectName("ContentBrowser");
	m_Layout = new QHBoxLayout();
	m_Layout->setSpacing(0);
	m_Layout->setContentsMargins(0, 0, 0, 0);

	m_Layout->addWidget(directory = new CBDirectory("../../StaticData"),1);
	m_Layout->addWidget(folderDataHolder = new CBFolderDataHolder(), 5);
	directory->SetCBFolderData(folderDataHolder->folderData);


	setLayout(m_Layout);
	SetQssFile("\\CSS\\ContentBrowser.qss");
}
