#pragma once
#include "ImgnButton.h"
class QMenu;

class FolderButton : public ImgnButton
{
public:
	FolderButton(bool hasMenu = true);
	~FolderButton();

	void SetCheckedMenu(bool checked);
protected:
	virtual void mousePressEvent(QMouseEvent *) override;

private:
	QMenu* menu;
};

