#include "DetailsLayout.h"
#include "Qt\qmenubar.h"
#include "ImgnComponent.h"
#include "MovementComponent.h"
#include "MeshComponent.h"
#include "GravityComponent.h"
#include "PathFollowerComponent.h"
#include "ImgnAction.h"
#include "Qt\qscrollarea.h"
#include "Entity.h"
#include "ImgnCreateComponent.h"
#include "Qt\qpushbutton.h"
#include "Qt\qboxlayout.h"

DetailsLayout* DetailsLayout::detailsLayout = 0;

DetailsLayout::DetailsLayout()
{
	Initialize();
}


DetailsLayout::~DetailsLayout()
{
	
}

void DetailsLayout::Initialize()
{
	numComponents = 0;
	numAddableComponenets = 0;

	scrollArea = new QScrollArea;
	m_Layout = new QVBoxLayout(scrollArea);
	//m_Layout->setSpacing(0);
	m_Layout->setContentsMargins(14,25,14,25);

	addComponentButton = new QPushButton("Add Component",this);
	componentMenu = new QMenu();

	m_Layout->addWidget(addComponentButton);
	addComponentButton->setStyleSheet("QPushButton:enabled { border: 1px solid black; background-color:"
		"qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 rgb(255,255,255), stop: 1 rgb(150,150,150)); border-radius:2px; padding: 5px;}"
		"QPushButton:pressed { border: 1.5px solid black; background-color:"
		"qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 rgb(235,235,235), stop: 1 rgb(130,130,130)); border-radius:3px; padding: 5px;}"
		"QPushButton {font-size: 16px; color: solid black;subcontrol-position: bottom center;}"
		"QPushButton::menu-indicator{ subcontrol-position: right center; subcontrol-origin: padding; left: -5px;}");
	CreateActions();
	CreateMenu();
	addComponentButton->setMenu(componentMenu);

	setLayout(m_Layout);

	setFrameShape(QFrame::Shape::Box);
	setFrameShadow(QFrame::Shadow::Sunken);
	setLineWidth(2);
	setObjectName("DetailsLayout");
	setStyleSheet("QFrame#DetailsLayout { margin: 0px; background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: .5, stop: 0 rgb(224,255,255), stop: .5 rgb(214,250,255));"
		"background: qlineargradient(x1 : 0, y1 : .5, x2 : 0, y2 : 1, stop : .5 rgb(204, 245, 255), stop : 1 rgb(194, 240, 255));}"
		""
		"QGroupBox {font-size: 14px; font-weight: bold; border:2px solid black; border-radius:5px; margin-top: 1ex;}"
		"QGroupBox::title { padding: 0 3px; margin-top:-7px; subcontrol-origin: margin; subcontrol-position: top center; }");
	setMaximumHeight(1000);
	m_Layout->setAlignment(Qt::AlignTop);

	Resize();
}

void DetailsLayout::ClearFocus()
{
}

void DetailsLayout::Resize()
{
	int biggestWidth = 250;
	for (int i = 0; i < numComponents; i++)
	{
		if (biggestWidth <= components[i]->size().width())
			biggestWidth = components[i]->size().width() + 30;
		//height += groupBox[i]->size().height();
	}
	setMaximumWidth(biggestWidth);
}

void DetailsLayout::SetEntity(Imgn::Entity * entity)
{
	components = currentEntity->GetComponents();
	for (int i = 0; i < numComponents; i++)
	{
		components[i]->setVisible(false);
	}

	currentEntity = entity;
	components = currentEntity->GetComponents();
	numComponents = currentEntity->GetNumComponents();
	
	for (int i = 0; i < numComponents; i++)
	{
		AddComponent((char*)components[i]->GetName(), components[i], i);
	}

	Resize();
}

void DetailsLayout::UpdateComponents()
{
	components = currentEntity->GetComponents();
	numComponents = currentEntity->GetNumComponents();
	for (int i = 0; i < numComponents; i++)
	{
		components[i]->setVisible(false);
	}
	for (int i = 0; i < numComponents; i++)
	{
		AddComponent((char*)components[i]->GetName(), components[i], i);
	}
}

void DetailsLayout::AddComponent(char*, ImgnComponent* widget,int)
{
	if (!widget->layoutInitalized)
	{
		widget->CreateWidgets();
	}
	if (widget->layoutHasData)
	{
		m_Layout->addWidget(widget, 0, Qt::AlignTop);
		widget->setParent(this);
		widget->setVisible(true);
	}

	m_Layout->removeWidget(addComponentButton);
	m_Layout->addWidget(addComponentButton,0,Qt::AlignTop);
	m_Layout->setContentsMargins(14, 25, 14, 25);
}



void DetailsLayout::CreateActions()
{
	createNewButton = new QAction("Create New", this);
	componentMenu->addAction(createNewButton);
	componentMenu->addSeparator();
	connect(createNewButton, SIGNAL(triggered()), this, SLOT(CreateNewComponent()));

	CreateAction<MovementComponent>();
	CreateAction<MeshComponent>();
	CreateAction<GravityComponent>();
	CreateAction<PathFollowerComponent>();
	
	
	componentMenu->setStyleSheet("");
}

void DetailsLayout::CreateMenu()
{
	
}

void DetailsLayout::CreateNewComponent()
{
	createComponent = new Imgn::ImgnCreateComponent(this);
}


void DetailsLayout::ButtonPressed()
{
	QObject* sender = QObject::sender();
	string objectName = sender->objectName().toLocal8Bit().constData();

	for (int i = 0; i < numAddableComponenets; i++)
	{
		if (addableComponents[i]->objectName() == objectName.c_str())
		{
			currentEntity->AddComponent(addableComponents[i]->t, objectName);
			break;
		}
	}
	UpdateComponents();
	Resize();
}
