#include "CBFile.h"
#include "Qt\qboxlayout.h"
#include "QtGui\QLabel"
#include "CBFilesButton.h"
#include "dirent.h"

CBFile::CBFile()
{
}

CBFile::CBFile(dirent* Entry)
{
	entry = Entry;
	name = entry->d_name;
	Initialize();
}

CBFile::~CBFile()
{
}

void CBFile::Initialize()
{
	m_layout = new QVBoxLayout;
	setLayout(m_layout);

	m_layout->addWidget(button = new CBFilesButton(entry),5, Qt::AlignCenter);

	m_layout->addWidget(fileName = new QLabel, 1, Qt::AlignBottom | Qt::AlignHCenter);
	fileName->setText(name.c_str());

	this->setObjectName("File");

	this->setFixedHeight(90);
}
