#include "CBFile.h"
#include "Qt\qboxlayout.h"
#include "QtGui\QLabel"
#include "CBFilesButton.h"
#include "dirent.h"

CBFile::CBFile()
{
}

CBFile::CBFile(dirent* Entry, std::string FilePath)
{
	entry = Entry;
	name = entry->d_name;
	filePath = FilePath;
	Initialize();
}

CBFile::~CBFile()
{
}

void CBFile::Initialize()
{
	m_layout = new QVBoxLayout;
	setLayout(m_layout);

	m_layout->addWidget(button = new CBFilesButton(entry, filePath),5, Qt::AlignCenter);

	m_layout->addWidget(fileNameLabel = new QLabel, 1, Qt::AlignBottom | Qt::AlignHCenter);
	fileNameLabel->setText(name.c_str());

	this->setObjectName("File");

	this->setFixedHeight(90);
}
