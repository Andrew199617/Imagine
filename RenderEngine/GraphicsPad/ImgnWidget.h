#pragma once
#include "QtGui\QWidget"

class ImgnWidget : public QWidget
{
public:
	ImgnWidget();
	~ImgnWidget();

protected:
	virtual void mousePressEvent(QMouseEvent* qm);
	virtual void Initialize() = 0;
	void SetQssFile(std::string fileLocation);
};

