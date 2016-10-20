#pragma once
#include "Qt\qframe.h"

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
};

