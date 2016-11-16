#include "ImgnMainWindow.h"
#include "FbxFileReader.h"
#include <QtGui\qboxlayout>
#include "MeGlWindow.h"
#include <iostream>
#include "SaveLogger.h"
#include <Qt\qmenu.h>
#include <Qt\qmenubar.h>
#include "Scene.h"
#include "SceneReader.h"
#include "Hierarchy.h"
#include "Qt\qpushbutton.h"
#include "DetailsLayout.h"
#include "MeGlWindow.h"
#include "ImgnViewport.h"
#include "ImgnToolBar.h"
#include "ImgnTool.h"
#include "ContentBrowser.h"

ImgnMainWindow::ImgnMainWindow(MeGlWindow* meGl)
{
	saveLogger = saveLogger->Instance();
	this->meGlWindow = meGl;

	
	QWidget *widget = new QWidget;
	setAttribute(Qt::WA_DeleteOnClose);
	setCentralWidget(widget);
	widget->setLayout(mainLayout = new QGridLayout);

	AddTools();
	AddHierarchy();
	AddGlWindow();
	AddObjectDetails();	
	AddContentBrowser();

	CreateActions();
	CreateMenus();

	this->setStyleSheet("QMainWindow {background: solid gray}");

	setWindowTitle(tr("Imagine"));
}

void ImgnMainWindow::CreateActions()
{
	openAct = new QAction(tr("&Open"), this);
	openAct->setShortcuts(QKeySequence::New);
	openAct->setStatusTip(tr("Open a new Scene"));
	connect(openAct, SIGNAL(triggered()), this, SLOT(openingFile()));

	saveAct = new QAction(tr("&Save"), this);
	saveAct->setShortcuts(QKeySequence::Save);
	saveAct->setStatusTip(tr("Save your game"));
	connect(saveAct, SIGNAL(triggered()), this, SLOT(Save()));

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

void ImgnMainWindow::CreateMenus()
{
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(openAct);
	fileMenu->addAction(saveAct);

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

void ImgnMainWindow::AddTools()
{
	imgnToolBar = new ImgnToolBar;
	mainLayout->addWidget(imgnToolBar, 1, 2, Qt::AlignHCenter);
	playButton = new QPushButton;
	ImgnTool* tool = new ImgnTool(playButton,new QPushButton("^"));
	imgnToolBar->AddTool(tool);
	QPixmap pixmap(tr("C:/Users/Andrew/Documents/Neumont/Imagine/StaticData/Images/Play.png"));
	playIcon = new QIcon(pixmap);
	pixmap.load(tr("C:/Users/Andrew/Documents/Neumont/Imagine/StaticData/Images/Pause.png"));
	pauseIcon = new QIcon(pixmap);

	playButton->setIcon(*playIcon);
	connect(playButton, SIGNAL(pressed()), this, SLOT(OnPlayButtonPress()));
}

void ImgnMainWindow::AddGlWindow()
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

void ImgnMainWindow::AddObjectDetails()
{
	mainLayout->addWidget(DetailsLayout::Instance(), 1, 3,3,1);
	DetailsLayout::Instance()->setMinimumWidth(250);
	DetailsLayout::Instance()->setMaximumWidth(320);
	
}

void ImgnMainWindow::AddHierarchy()
{
	hierarchyLayout = Hierarchy::Instance();
	mainLayout->addWidget(hierarchyLayout, 1, 1,2,1);
	hierarchyLayout->sizePolicy().setHorizontalPolicy(QSizePolicy::Policy::Maximum);
	hierarchyLayout->setMinimumWidth(250);
	hierarchyLayout->setMaximumWidth(320);
}

void ImgnMainWindow::AddContentBrowser()
{
	contentBrowser = new ContentBrowser();
	mainLayout->addWidget(contentBrowser, 3, 1, 1, 2);
}

void ImgnMainWindow::mousePressEvent(QMouseEvent *)
{
	DetailsLayout::Instance()->ClearFocus();

	//DELETE
	hierarchyLayout->ResetQssFile();

	if (focusWidget() != meGlWindow && focusWidget() != playButton)
	{
		meGlWindow->clearFocus();
	}
}

void ImgnMainWindow::leaveEvent(QEvent * e)
{
	QMainWindow::leaveEvent(e);
}

void ImgnMainWindow::closeEvent(QCloseEvent * ce)
{
	if (!meGlWindow->forceShutdown())
	{
		ce->ignore();
	}
	ce->accept();
	QMainWindow::closeEvent(ce);
	exit(0);
}

void ImgnMainWindow::WindowsShowEvent()
{
	QObject* object = QObject::sender();
	QString objectName = object->objectName();

	if (objectName == "ShowDetails")
	{
		DetailsLayout::Instance()->setHidden(!DetailsLayout::Instance()->isHidden());
	}
	else if (objectName == "ShowTools")
	{
		imgnToolBar->setHidden(!imgnToolBar->isHidden());
	}
	else if (objectName == "ShowHierarchy")
	{
		hierarchyLayout->SetHidden(!hierarchyLayout->IsHidden());
	}
}

void ImgnMainWindow::openingFile()
{
	string str = openFileDialog.GetFile();
	saveLogger->Open(str.c_str());
}

void ImgnMainWindow::AddObject()
{
	SceneReader* scenereader = new SceneReader;
	FbxFileReader fileReader;

	string str = openFileDialog.GetFile();
	string ObjName = fileReader.GetName(str);
	string sceneName = "..\\..\\StaticData\\Scenes\\" + ObjName + ".imgnasset";

	Scene* scene = scenereader->ReadSceneFile(sceneName);
	if (!scene)
	{
		fileReader.Initialize(str);
	}
	saveLogger->AddObj(ObjName);
	delete scenereader;
	
}

void ImgnMainWindow::AddCube()
{
	saveLogger->AddObj("Cube","Cube");
}

void ImgnMainWindow::AddSphere()
{
	saveLogger->AddObj("Sphere","Sphere");
}

void ImgnMainWindow::AddPlane()
{
	saveLogger->AddObj("Plane","Plane");
}

void ImgnMainWindow::OnPlayButtonPress()
{
	if (!meGlWindow->viewport->IsPlaying())
	{
		playButton->setIcon(*pauseIcon);
	}
	else
	{
		playButton->setIcon(*playIcon);
	}
	meGlWindow->setFocus();
	meGlWindow->viewport->SetIsPlaying(!meGlWindow->viewport->IsPlaying());
}

void ImgnMainWindow::Save()
{
	ImgnViewport::entityManager.SaveEntities();
}
