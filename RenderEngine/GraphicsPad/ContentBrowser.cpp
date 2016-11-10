#include "ContentBrowser.h"
#include "dirent.h"
#include <string.h>
#include <iostream>
#include "ImgnFolder.h"
#include "Qt\qboxlayout.h"
#include "Qt\qpushbutton.h"
#include "CBDirectory.h"


ContentBrowser::ContentBrowser() : ImgnFrame()
{
	Initialize();
}


ContentBrowser::~ContentBrowser()
{
}

void ContentBrowser::Initialize()
{
	this->setObjectName("ContentBrowser");
	m_Layout = new QHBoxLayout();
	m_Layout->setSpacing(0);
	m_Layout->setContentsMargins(0, 0, 0, 0);
	directory = new CBDirectory("../../StaticData");
	m_Layout->addWidget(directory,1);
	
	m_Layout->addLayout(filesHolder = new QVBoxLayout, 5);
	setLayout(m_Layout);

	SetQssFile("\\CSS\\ContentBrowser.qss");
	//GetData();
}
