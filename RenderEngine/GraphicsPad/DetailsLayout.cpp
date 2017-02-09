#include "DetailsLayout.h"
#include "Qt\qmenubar.h"
#include "ImgnComponent.h"
#include "MovementComponent.h"
#include "MeshComponent.h"
#include "Physics/RigidBody.h"
#include "ImgnAction.h"
#include "Qt\qscrollarea.h"
#include "Entity.h"
#include "ImgnCreateComponent.h"
#include "Qt\qpushbutton.h"
#include "Qt\qboxlayout.h"
#include "Qt\qfile.h"
#include "Qt\qdir.h"
#include <windows.h>
#include "CollisionDetection\BoxCollider.h"
#include "CollisionDetection\SphereCollider.h"
#include "QtGui\QLabel"
#include "Qt\qlineedit.h"
#include "SaveLogger.h"
#include "Hierarchy.h"
#include "ImgnLabel.h"
typedef void* (*ADDCOMPONENTS)(string*);

using std::cout;
using std::endl;

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
	m_Layout->addWidget(new ImgnLabel("Details"), 0, Qt::AlignHCenter);
	m_Layout->addSpacing(15);

	addComponentButton = new QPushButton("Add Component",this);
	componentMenu = new QMenu();

	QHBoxLayout* nameLayout = new QHBoxLayout;
	nameLayout->addWidget(new QLabel("Entity Name: "), 0, Qt::AlignHCenter);
	nameLayout->addWidget(entityName = new QLineEdit(""), 0, Qt::AlignLeft);
	connect(entityName, SIGNAL(returnPressed()), this, SLOT(ChangeName()));
	m_Layout->addLayout(nameLayout);
	m_Layout->addSpacing(15);

	m_Layout->addWidget(addComponentButton);
	addComponentButton->setStyleSheet("QPushButton:enabled { border: 1px solid black; background-color:"
		"qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 rgb(255,255,255), stop: 1 rgb(150,150,150)); border-radius:2px; padding: 5px;}"
		"QPushButton:pressed { border: 1.5px solid black; background-color:"
		"qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 rgb(235,235,235), stop: 1 rgb(130,130,130)); border-radius:3px; padding: 5px;}"
		"QPushButton {font-size: 16px; color: solid black;subcontrol-position: bottom center;}"
		"QPushButton::menu-indicator{ subcontrol-position: right center; subcontrol-origin: padding; left: -5px;}");
	CreateActions();
	addComponentButton->setMenu(componentMenu);
	connect(componentMenu, SIGNAL(aboutToShow()), this, SLOT(ResizeMenu()));

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
	
	string outputDir = QDir::currentPath().toLocal8Bit().data();
	string fileName = "\\CSS\\QMenu.qss";
	QFile file((outputDir + fileName).c_str());
	file.open(QFile::ReadOnly);
	QString styleSheet = QLatin1String(file.readAll());
	componentMenu->setStyleSheet(styleSheet);
	file.close();
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
		if (biggestWidth <= components[i]->size().width() && components[i]->size().width() <= 348)
			biggestWidth = components[i]->size().width() + 30;
		//height += groupBox[i]->size().height();
	}
	setMaximumWidth(biggestWidth);
}

void DetailsLayout::SetEntity(Imgn::Entity* entity)
{
	components = currentEntity->GetComponents();
	for (int i = 0; i < numComponents; i++)
	{
		components[i]->setVisible(false);
	}

	currentEntity = entity;
	//AddEntityData(entity);
	entityName->setText(currentEntity->GetName());
	components = currentEntity->GetComponents();
	numComponents = currentEntity->GetNumComponents();
	
	for (int i = 0; i < numComponents; i++)
	{
		AddComponent((char*)components[i]->GetName(), components[i], i);
	}
	m_Layout->removeWidget(addComponentButton);
	m_Layout->addWidget(addComponentButton, 0, Qt::AlignTop);
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
	m_Layout->removeWidget(addComponentButton);
	m_Layout->addWidget(addComponentButton, 0, Qt::AlignTop);
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
}

void DetailsLayout::CreateActions()
{
	createNewButton = new QAction("Create New", this);
	componentMenu->addAction(createNewButton);
	componentMenu->addSeparator();
	connect(createNewButton, SIGNAL(triggered()), this, SLOT(CreateNewComponent()));

	CreateAction<Imgn::RigidBody>("Rigid Body");
	CreateAction<BoxCollider>();
	CreateAction<SphereCollider>();
	componentMenu->addSeparator();
	CreateAction<MovementComponent>();
	CreateAction<MeshComponent>();
}

void DetailsLayout::CreateMenu()
{
	
	HINSTANCE hDLL;
	LPCWSTR dll = L"GameName.dll";
	hDLL = LoadLibrary(dll);
	ADDCOMPONENTS AddComponents;

	if (hDLL)
	{
		AddComponents = (ADDCOMPONENTS)GetProcAddress(hDLL, "AddActionToDetailsLayout");
		if (!AddComponents)
		{
			// handle the error
			FreeLibrary(hDLL);
			cout << "function not found for dll." << endl;
		}
		else
		{
			string name;
			void* test = AddComponents(&name);
			string objectName = name.substr(6, name.npos);
			for (unsigned i = 1; i < objectName.length(); i++)
			{
				if (isupper(objectName.at(i)))
				{
					objectName += ' ';
					for (unsigned j = objectName.length(); j > i; j--)
					{
						objectName[j] = objectName[j - 1];
					}
					objectName[i] = ' ';
					objectName += ' ';
					objectName[objectName.length() - 1] = '\0';
					i += 2;
				}
			}
			addableComponents[numAddableComponenets] = new ImgnAction(objectName.c_str(), this);
			addableComponents[numAddableComponenets]->t = test;
			addableComponents[numAddableComponenets]->setObjectName(objectName.c_str());
			connect(addableComponents[numAddableComponenets], SIGNAL(triggered()), this, SLOT(ButtonPressed()));
			componentMenu->addAction(addableComponents[numAddableComponenets]);
			numAddableComponenets++;
		}
	}
}

void DetailsLayout::CreateNewComponent()
{
	createComponent = new Imgn::ImgnCreateComponent(this);
}

void DetailsLayout::ResizeMenu()
{
	componentMenu->setFixedWidth(addComponentButton->width());
}

void DetailsLayout::ChangeName()
{
	string newName = entityName->text().toLocal8Bit().data();
	SaveLogger::Instance()->SetEntityName(currentEntity->GetName(), newName);
	Hierarchy::Instance()->SetEntityName(currentEntity, newName);
	currentEntity->SetName(newName);
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
			UpdateComponents();
			Resize();
			break;
		}
	}
}
