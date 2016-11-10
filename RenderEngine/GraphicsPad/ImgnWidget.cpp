#include "ImgnWidget.h"
#include <string.h>
#include "Qt\qdir.h"
#include "Qt\qfile.h"


ImgnWidget::ImgnWidget()
{
}


ImgnWidget::~ImgnWidget()
{
}

void ImgnWidget::mousePressEvent(QMouseEvent* qm)
{
	QWidget::mousePressEvent(qm);
	setFocus();
}

void ImgnWidget::SetQssFile(std::string fileLocation)
{
	std::string outputDir = QDir::currentPath().toLocal8Bit().data();
	QFile file((outputDir + fileLocation).c_str());
	file.open(QFile::ReadOnly);
	QString styleSheet = QLatin1String(file.readAll());
	setStyleSheet(styleSheet);
	file.close();
}
