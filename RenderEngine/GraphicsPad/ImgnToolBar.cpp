#include "ImgnToolBar.h"
#include <string>
#include "Qt\qfile.h"
#include "Qt\qdir.h"

using std::string;

ImgnToolBar::ImgnToolBar()
{
	Initialize();
}


ImgnToolBar::~ImgnToolBar()
{
}

void ImgnToolBar::Initialize()
{
	string outputDir = QDir::currentPath().toLocal8Bit().data();
	string fileName = "\\CSS\\ImgnToolBar.qss";
	QFile file((outputDir + fileName).c_str());
	file.open(QFile::ReadOnly);
	QString styleSheet = QLatin1String(file.readAll());
	setStyleSheet(styleSheet);
	file.close();
}
