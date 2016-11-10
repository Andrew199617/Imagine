#pragma once
#include "ImgnButton.h"
class QMenu;

class FolderButton : public ImgnButton
{
public:
	FolderButton();
	~FolderButton();

	void SetCheckedMenu(bool checked);
protected:
	virtual void mousePressEvent(QMouseEvent *) override;
	virtual void mouseDoubleClickEvent(QMouseEvent *) override;

private:
	QMenu* menu;
};

