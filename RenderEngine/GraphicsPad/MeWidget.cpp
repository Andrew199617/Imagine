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
#include "OpenFileDialog.h"
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
	mainLayout->addWidget(meGlWindow);
	controlsLayout->addWidget(discardBasedOnDepth = new QCheckBox("Discard pixels based on depth"));
	controlsLayout->addWidget(useRegularDepth = new QCheckBox("Regular Depth"));
	controlsLayout->addWidget(submit = new QPushButton("Submit"));
	discardBasedOnDepth->setChecked(true);
	useRegularDepth->setChecked(false);
	PostProcessingModel::discardBasedOnDepth = discardBasedOnDepth->isChecked();
	PostProcessingModel::regularDepth = useRegularDepth->isChecked();

	createActions();
	createMenus();

	setWindowTitle(tr("Imagine Engine"));
	connect(submit, SIGNAL(released()), this, SLOT(openingTexture()));
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
	OpenFileDialog openFileDialog1;

	string str = openFileDialog1.getFile();
	SaveLogger::intialize(str.c_str());
}

void MeWidget::openingTexture()
{
	PostProcessingModel::discardBasedOnDepth = discardBasedOnDepth->isChecked();
	PostProcessingModel::regularDepth = useRegularDepth->isChecked();
}

void MeWidget::checkBoxChanged()
{
}

void MeWidget::createActions()
{
	openAct = new QAction(tr("&Open"), this);
	openAct->setShortcuts(QKeySequence::New);
	openAct->setStatusTip(tr("Open a new Obj"));
	connect(openAct, SIGNAL(triggered()), this, SLOT(openingFile()));

}

void MeWidget::createMenus()
{
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(openAct);
	fileMenu->addSeparator();

}
