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



MeWidget::MeWidget(MeGlWindow* meGl, MeModel* model)
{
	SaveLogger::intialize();
	theModel = model;
	this->meGlWindow = meGl;

	QWidget *widget = new QWidget;
	setCentralWidget(widget);
	QVBoxLayout* mainLayout;
	widget->setLayout(mainLayout = new QVBoxLayout);
	mainLayout->addLayout(controlsLayout = new QVBoxLayout);
	mainLayout->addLayout(objectDetailsLayout = new QVBoxLayout);
	mainLayout->addWidget(meGlWindow);

	createActions();
	createMenus();

	setWindowTitle(tr("Imagine Engine"));
}

string getStringFromQstring(QString qstr)
{
	std::string current_locale_text = qstr.toLocal8Bit().constData();
	return current_locale_text;
}

void MeWidget::sliderValueChanged()
{
	theModel->uD = uD->value();
	theModel->uR = uR->value();
}

void MeWidget::openingFile()
{
	string str = openFileDialog.getFile();
	SaveLogger::intialize(str.c_str());
}

void MeWidget::openingTexture()
{
	string str = openFileDialog.getFile();
	SaveLogger::AddObj(str);
}

void MeWidget::checkBoxChanged()
{
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
	connect(addObjectAct, SIGNAL(triggered()), this, SLOT(openingTexture()));

}

void MeWidget::createMenus()
{
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(openAct);
	fileMenu->addSeparator();

	gameObjectMenu = menuBar()->addMenu(tr("&GameObject"));
	gameObjectMenu->addAction(addObjectAct);
	gameObjectMenu->addSeparator();

}
