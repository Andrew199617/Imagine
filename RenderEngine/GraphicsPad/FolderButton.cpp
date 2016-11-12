#include "FolderButton.h"
#include "Qt\qmenu.h"



FolderButton::FolderButton(bool hasMenu)
{
	setCheckable(true);
	if (hasMenu)
	{
		setMenu(menu = new QMenu);
	}
}


FolderButton::~FolderButton()
{
}

void FolderButton::SetCheckedMenu(bool checked)
{
	std::string str = "subcontrol - position: left center; subcontrol - origin: padding; left: 5 px; top: 1px;";
	if (checked)
	{
		std::string ch = styleSheet().toLocal8Bit().data();
		std::string css = "image: url(C:/Users/Andrew/Documents/Neumont/Imagine/StaticData/Images/Right_Arrow.png); }";
		setStyleSheet(styleSheet() + ("QPushButton::menu-indicator {" + css).c_str());
	}
	else
	{
		std::string ch = styleSheet().toLocal8Bit().data();
		std::string css = "image: url(C:/Users/Andrew/Documents/Neumont/Imagine/StaticData/Images/Down_Arrow.png); }";
		setStyleSheet(styleSheet() + ("QPushButton::menu-indicator {" + css).c_str());
	}
}


void FolderButton::mousePressEvent(QMouseEvent *qme)
{
	QWidget::mousePressEvent(qme);
	setFocus();
	setChecked(true);
	emit pressed();
}
