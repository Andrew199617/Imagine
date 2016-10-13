#pragma once
#pragma warning(push)
#pragma warning (disable:4251)
#pragma warning (disable:4127)
#include "QtGui\qboxlayout.h"
#include "TransformLayout.h"
#pragma warning(pop)
#include <Qt\qgroupbox.h>
#include "QtGui\qpushbutton.h"
#include <Qt\qmenu.h>
#include <Qt\qmenubar.h>
#include "EntityData.h"

class DetailsLayout :
	public QVBoxLayout
{
	Q_OBJECT

public:
	DetailsLayout();
	~DetailsLayout();

	void ClearFocus();
	void SetHidden(bool);
	bool isHidden;
	QFrame* frame;

	void AddComponent(char* name, QLayout* layout);

private:
	void CreateActions();

private slots:
	void ButtonPressed();

private:
	int numComponents;
	QGroupBox* groupBox[MAX_COMPONENTS];
	//ObjectDetailsLayout* objectDetailsLayout;
	TransformLayout* transformLayout;
	QPushButton* addComponentButton;
	QMenu* componentMenu;
	QAction* components[50];
};

