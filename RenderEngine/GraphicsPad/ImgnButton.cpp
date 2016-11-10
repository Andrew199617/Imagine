#include "ImgnButton.h"



ImgnButton::ImgnButton()
{
}


ImgnButton::~ImgnButton()
{
}

void ImgnButton::mouseDoubleClickEvent(QMouseEvent *qme)
{
	QPushButton::mouseDoubleClickEvent(qme);
	emit DoubleClicked();
}
