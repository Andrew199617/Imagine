#include "FbxFileReader.h"
#pragma warning(push)
#pragma warning(push)
#pragma warning (disable:4127)
#include "MeWidget.h"
#pragma warning(pop)
#include "Slider.h"
#pragma warning(push)
#pragma warning (disable:4127)
#pragma warning (disable:4251)
#include <Qt\qdebug.h>
#pragma warning(pop)
#include <QtGui\qhboxlayout>
#include "MeGlWindow.h"
#include <iostream>
#include "SaveLogger.h"
#include <Qt\qmenu.h>
#include <Qt\qmenubar.h>
#include <QtGui\qtabwidget.h>
#include "Scene.h"
#include "SceneReader.h"
#include <Qt\qgroupbox.h>
#include "OriginalGame.h"

MeWidget::MeWidget(MeGlWindow* meGl, MeModel* model)
{
	SaveLogger::intialize();
	theModel = model;
	this->meGlWindow = meGl;

	
	QWidget *widget = new QWidget;
	setCentralWidget(widget);
	widget->setLayout(mainLayout = new QGridLayout);

	AddTools();
	AddHierarchy();
	AddGlWindow();
	AddObjectDetails();

	CreateActions();
	CreateMenus();

	setWindowTitle(tr("Imagine"));
}

void MeWidget::CreateActions()
{
	openAct = new QAction(tr("&Open"), this);
	openAct->setShortcuts(QKeySequence::New);
	openAct->setStatusTip(tr("Open a new Scene"));
	connect(openAct, SIGNAL(triggered()), this, SLOT(openingFile()));

	addObjectAct = new QAction(tr("&Add Object"), this);
	addObjectAct->setShortcuts(QKeySequence::AddTab);
	addObjectAct->setStatusTip(tr("Open a new Obj"));
	connect(addObjectAct, SIGNAL(triggered()), this, SLOT(AddObject()));

	addCubeAct = new QAction(tr("&Add Cube"), this);
	addCubeAct->setStatusTip(tr("Add a cube to the scene."));
	connect(addCubeAct, SIGNAL(triggered()), this, SLOT(AddCube()));

	addSphereAct = new QAction(tr("&Add Sphere"), this);
	addSphereAct->setStatusTip(tr("Add a Sphere to the scene."));
	connect(addSphereAct, SIGNAL(triggered()), this, SLOT(AddSphere()));

	addPlaneAct = new QAction(tr("&Add Plane"), this);
	addPlaneAct->setStatusTip(tr("Add a Plane to the scene."));
	connect(addPlaneAct, SIGNAL(triggered()), this, SLOT(AddPlane()));

	showDetails = new QAction(tr("&Details"), this);
	showDetails->setObjectName("ShowDetails");
	showDetails->setStatusTip(tr("Show/Hide the Details panel."));
	connect(showDetails, SIGNAL(triggered()), this, SLOT(WindowsShowEvent()));

	showTools = new QAction(tr("&Tools"), this);
	showTools->setObjectName("ShowTools");
	showTools->setStatusTip(tr("Show/Hide the Tools panel."));
	connect(showTools, SIGNAL(triggered()), this, SLOT(WindowsShowEvent()));

	showHierarchy = new QAction(tr("&Hierarchy"), this);
	showHierarchy->setObjectName("ShowHierarchy");
	showHierarchy->setToolTip(tr("Show/Hide the Hierarchy panel."));
	connect(showHierarchy, SIGNAL(triggered()), this, SLOT(WindowsShowEvent()));
}

void MeWidget::CreateMenus()
{
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(openAct);
	fileMenu->addSeparator();

	gameObjectMenu = menuBar()->addMenu(tr("&GameObject"));
	gameObjectMenu->addAction(addObjectAct);
	gameObjectMenu->addAction(addCubeAct);
	gameObjectMenu->addAction(addSphereAct);
	gameObjectMenu->addAction(addPlaneAct);

	windowMenu = menuBar()->addMenu(tr("&Window"));
	windowMenu->addAction(showDetails);
	windowMenu->addAction(showTools);
	windowMenu->addAction(showHierarchy);

	QPalette palette = fileMenu->palette();
	palette.setColor(backgroundRole(), QColor(224, 255, 255));
	palette.setColor(foregroundRole(), QColor(224, 255, 255));
	fileMenu->setPalette(palette);
	fileMenu->setAutoFillBackground(true);
	gameObjectMenu->setPalette(palette);
	gameObjectMenu->setAutoFillBackground(true);
	windowMenu->setPalette(palette);
	windowMenu->setAutoFillBackground(true);

}

void MeWidget::AddTools()
{
	mainLayout->addLayout(toolsLayout = new QHBoxLayout, 1, 2);
	toolsLayout->addWidget(playButton = new QPushButton);
	QPixmap pixmap(tr("C:/Users/Andrew/Documents/Neumont/Imagine/StaticData/Images/Play.png"));
	playIcon = new QIcon(pixmap);
	pixmap.load(tr("C:/Users/Andrew/Documents/Neumont/Imagine/StaticData/Images/Pause.png"));
	pauseIcon = new QIcon(pixmap);

	playButton->setIcon(*playIcon);
	QSize iconSize(25, 25);
	playButton->setIconSize(iconSize);
	playButton->setFixedSize(iconSize);
	connect(playButton, SIGNAL(pressed()), this, SLOT(OnPlayButtonPress()));
}

void MeWidget::AddGlWindow()
{
	meGlWindowLayout = new QHBoxLayout;
	QFrame* frame = new QFrame;
	frame->setLayout(meGlWindowLayout);
	frame->setFrameShape(QFrame::Shape::Box);
	frame->setFrameShadow(QFrame::Shadow::Sunken);
	frame->setLineWidth(2);
	QSizePolicy sp(QSizePolicy::Expanding, QSizePolicy::Expanding);
	frame->setSizePolicy(sp);
	mainLayout->addWidget(frame, 2, 2);
	meGlWindowLayout->setMargin(1);
	meGlWindowLayout->addWidget(meGlWindow);
	frame->setMinimumWidth(1280);
	frame->setMinimumHeight(720);
	frame->setMaximumWidth(1920);
	frame->setMaximumHeight(1080);

}

void MeWidget::AddObjectDetails()
{
	detailsLayout = new DetailsLayout;
	mainLayout->addWidget(detailsLayout->frame, 2, 3);
}

void MeWidget::AddHierarchy()
{
	hierarchyLayout = new Hierarchy;
	mainLayout->addWidget(hierarchyLayout->GetWidget(), 2, 1);
	hierarchyLayout->GetWidget()->sizePolicy().setHorizontalPolicy(QSizePolicy::Policy::Maximum);
	hierarchyLayout->GetWidget()->setMinimumWidth(250);
	hierarchyLayout->GetWidget()->setMaximumWidth(320);
}

void MeWidget::mousePressEvent(QMouseEvent *)
{
	detailsLayout->ClearFocus();
}

void MeWidget::WindowsShowEvent()
{
	QObject* object = QObject::sender();
	QString objectName = object->objectName();

	if (objectName == "ShowDetails")
	{
		detailsLayout->SetHidden(!detailsLayout->isHidden);
	}
	else if (objectName == "ShowTools")
	{
		playButton->setHidden(!playButton->isHidden());
	}
	else if (objectName == "ShowHierarchy")
	{
		hierarchyLayout->SetHidden(!hierarchyLayout->IsHidden());
	}
}

void MeWidget::openingFile()
{
	string str = openFileDialog.getFile();
	SaveLogger::intialize(str.c_str());
}

void MeWidget::AddObject()
{
	SceneReader scenereader;
	FbxFileReader fileReader;

	string str = openFileDialog.getFile();
	string ObjName = fileReader.GetName(str);
	string sceneName = "..\\..\\StaticData\\Scenes\\" + ObjName + ".scene";

	Scene* scene = scenereader.ReadSceneFile(sceneName);
	if (!scene)
	{
		fileReader.Initialize(str);
	}
	else
	{
		delete scene;
	}
	SaveLogger::AddObj(ObjName);
	
}

void MeWidget::AddCube()
{
	SaveLogger::AddObj("Cube");
}

void MeWidget::AddSphere()
{
	SaveLogger::AddObj("Sphere");
}

void MeWidget::AddPlane()
{
	SaveLogger::AddObj("Plane");
}

void MeWidget::OnPlayButtonPress()
{
	if (!meGlWindow->game->isPlaying)
	{
		playButton->setIcon(*pauseIcon);
	}
	else
	{
		playButton->setIcon(*playIcon);
	}
	meGlWindow->game->isPlaying = !meGlWindow->game->isPlaying;
}
