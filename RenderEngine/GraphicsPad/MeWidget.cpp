#include "FbxFileReader.h"
#include "SceneMaker.h"
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


MeWidget::MeWidget(MeGlWindow* meGl, MeModel* model)
{
	SaveLogger::intialize();
	theModel = model;
	this->meGlWindow = meGl;

	QWidget *widget = new QWidget;
	setCentralWidget(widget);
	QGridLayout* mainLayout;
	widget->setLayout(mainLayout = new QGridLayout);
	mainLayout->addLayout(controlsLayout = new QVBoxLayout,1,1);
	mainLayout->addLayout(new QVBoxLayout, 1, 2);
	mainLayout->addLayout(objectDetailsLayout = new QVBoxLayout,2,2);
	objectDetailsLayout->addWidget(discardBasedOnDepth = new QCheckBox);
	discardBasedOnDepth->hide();
	objectDetailsLayout->setMargin(0);
	mainLayout->addLayout(meGlWindowLayout = new QHBoxLayout,2,1);
	meGlWindowLayout->addWidget(meGlWindow);
	controlsLayout->addWidget(ShowDetails = new QPushButton("Show Details"));
	connect(ShowDetails, SIGNAL(released()), this, SLOT(sliderValueChanged()));

	createActions();
	createMenus();

	setWindowTitle(tr("Imagine"));
}

void MeWidget::createActions()
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
}

void MeWidget::createMenus()
{
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(openAct);
	fileMenu->addSeparator();

	gameObjectMenu = menuBar()->addMenu(tr("&GameObject"));
	gameObjectMenu->addAction(addObjectAct);
	gameObjectMenu->addAction(addCubeAct);
	gameObjectMenu->addAction(addSphereAct);
	gameObjectMenu->addAction(addPlaneAct);

}

string getStringFromQstring(QString qstr)
{
	std::string current_locale_text = qstr.toLocal8Bit().constData();
	return current_locale_text;
}

void MeWidget::sliderValueChanged()
{
	discardBasedOnDepth->setHidden(!discardBasedOnDepth->isHidden());
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

void MeWidget::checkBoxChanged()
{
}
