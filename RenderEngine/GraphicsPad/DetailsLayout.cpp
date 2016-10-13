#include "DetailsLayout.h"
#include "Qt\qmenubar.h"

DetailsLayout::DetailsLayout()
{
	numComponents = 0;
	isHidden = false;

	frame = new QFrame;
	AddComponent("Transform",transformLayout = new TransformLayout);
	this->addWidget(addComponentButton = new QPushButton("Add Component"));
	componentMenu = new QMenu();
	CreateActions();
	addComponentButton->setMenu(componentMenu);
	addComponentButton->showMenu();
	//connect(addComponentButton, SIGNAL(pressed()), this, SLOT(ButtonPressed()));

	frame->setLayout(this);
	frame->setFrameShape(QFrame::Shape::Box);
	frame->setFrameShadow(QFrame::Shadow::Sunken);
	frame->setLineWidth(2);
	frame->setContentsMargins(QMargins(5,5,5,5));
	QPalette palette = frame->palette();
	palette.setColor(frame->backgroundRole(), QColor(224, 255, 255));
	frame->setPalette(palette);
	frame->setAutoFillBackground(true);
}


DetailsLayout::~DetailsLayout()
{
}

void DetailsLayout::ClearFocus()
{
	transformLayout->ClearFocus();
}

void DetailsLayout::SetHidden(bool IsHidden)
{
	isHidden = IsHidden;
	groupBox[0]->setHidden(IsHidden);
	transformLayout->SetHidden(IsHidden);
	frame->setHidden(IsHidden);
}

void DetailsLayout::AddComponent(char* name, QLayout* layout)
{
	groupBox[numComponents] = new QGroupBox(name);
	groupBox[numComponents]->setLayout(layout);
	this->addWidget(groupBox[numComponents]);
	groupBox[numComponents]->setMaximumSize(320, 150);
	groupBox[numComponents]->setMinimumSize(250, 100);
	groupBox[numComponents]->setStyleSheet(
		"QGroupBox{"
		"border:2px solid black;"
		"border-radius:5px;"
		"margin-top: 6px;}"
		"QGroupBox::title {"
		"margin-top: -12px;} ");
	transformLayout->SetMaximumSize(60, 30);
	groupBox[numComponents]->sizePolicy().setHorizontalPolicy(QSizePolicy::Policy::Maximum);
	numComponents++;

	int biggestWidth = INT_MIN;
	int height = 50;
	for (int i = 0; i < numComponents; i++)
	{
		if(biggestWidth < groupBox[i]->size().width())
			biggestWidth = groupBox[i]->size().width()+ 20;
		height += groupBox[i]->size().height();
	}
	if (height > 1000)
	{
		height = 1000;
	}
	frame->setMaximumSize(biggestWidth,height);

}

void DetailsLayout::CreateActions()
{
	components[0] = new QAction("TestComponent",this);
	components[0]->setObjectName("TestComponent");
	connect(components[0], SIGNAL(triggered()), this, SLOT(ButtonPressed()));
	componentMenu->addAction(components[0]);
}


void DetailsLayout::ButtonPressed()
{
	QObject* sender = QObject::sender();
	QString objectName = sender->objectName();

	if (objectName == "TestComponent")
	{
		AddComponent("TestComponent", new TransformLayout);
	}
	this->removeWidget(addComponentButton);
	this->addWidget(addComponentButton);
}
