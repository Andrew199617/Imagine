#include "ImgnTool.h"
#include "Qt\qboxlayout.h"
#include "Qt\qpushbutton.h"
#include "Qt\qdir.h"
#include "Qt\qfile.h"

using std::string;

ImgnTool::ImgnTool()
{
	Initialize();
}

ImgnTool::ImgnTool(QPushButton * Tool, QPushButton * ExtraOptions)
{
	Initialize();
	m_Layout = new QHBoxLayout;
	m_Layout->setSpacing(0);
	m_Layout->setContentsMargins(7.5,5,7.5,5);
	tool = Tool;
	extraOptions = ExtraOptions;

	tool->setFixedSize(35, 35);
	QSize iconSize(25, 25);
	tool->setIconSize(iconSize);
	m_Layout->addWidget(tool,0,Qt::AlignLeft);
	if (extraOptions)
	{
		extraOptions->setFixedSize(10, 35);
		extraOptions->setIconSize(iconSize);
		m_Layout->addWidget(extraOptions, 0, Qt::AlignLeft);
		this->setFixedSize(60, 45);
	}
	else
	{
		this->setFixedSize(45, 45);
	}
	setLayout(m_Layout);
}

ImgnTool::~ImgnTool()
{
}

void ImgnTool::Initialize()
{
	tool = 0;
	extraOptions = 0;
	options = 0;
	this->setObjectName("ImgnTool");
}

void ImgnTool::SetQssFile()
{
	string outputDir = QDir::currentPath().toLocal8Bit().data();
	string fileName = "\\CSS\\ImgnTool.qss";
	QFile file((outputDir + fileName).c_str());
	file.open(QFile::ReadOnly);
	QString styleSheet = QLatin1String(file.readAll());
	setStyleSheet(styleSheet);
	file.close();
}
