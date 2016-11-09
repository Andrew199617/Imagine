#pragma once
#include "Qt\qframe.h"
#include <string.h>
#include "Qt\qdir.h"
#include "Qt\qfile.h"

class ImgnFrame :
	public QFrame
{
public:
	ImgnFrame() {}
	~ImgnFrame(){}
protected:
	virtual void mousePressEvent(QMouseEvent*)
	{
		setFocus();
	}
	virtual void Initialize() = 0;
	void SetQssFile(std::string fileLocation)
	{
		std::string outputDir = QDir::currentPath().toLocal8Bit().data();
		QFile file((outputDir + fileLocation).c_str());
		file.open(QFile::ReadOnly);
		QString styleSheet = QLatin1String(file.readAll());
		setStyleSheet(styleSheet);
		file.close();
	}
};

