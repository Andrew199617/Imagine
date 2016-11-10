#pragma once
#include "Qt\qpushbutton.h"

class ImgnButton :  public QPushButton
{
	Q_OBJECT
public:
	ImgnButton();
	~ImgnButton();
protected:
	virtual void mouseDoubleClickEvent(QMouseEvent *) override;

signals:
	void DoubleClicked();
};

