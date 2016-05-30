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
	OpenFileDialog openFileDialog1;

	string str = openFileDialog1.getFile();
	SaveLogger::intialize(str.c_str());
}

void MeWidget::openingTexture()
{
	OpenFileDialog openFileDialog1;

	string str = openFileDialog1.getFile();
	QString obj = QString::fromStdString(str);
	getTextureLocationLabel->setText(obj);
}

void MeWidget::checkBoxChanged()
{
	int svf = 1;
	if (save->text() == "Done" && svf == 1)
	{
		if (checkboxColor->isChecked())
		{
			svf += 2;
		}
		if (checkboxTexture->isChecked())
		{
			svf += 4;
		}
		if (checkboxNormals->isChecked())
		{
			svf += 8;
		}
		checkboxColor->hide();
		checkboxTexture->hide();
		checkboxNormals->hide();
		ObjName->hide();
		getFileLocation->hide();
		getFileLocationLabel->hide();
		getTextureLocation->hide();
		getTextureLocationLabel->hide();
		save->setText("Add another obj");
		string scenpath = "C:\\Users\\Andrew\\Documents\\Neumont\\Neumont Quarter Four\\gat_mvelez\\GAT160Middleware\\Data\\Scenes\\";
		SaveLogger::log(getStringFromQstring(ObjName->text()), getStringFromQstring(getTextureLocationLabel->text()), scenpath + getStringFromQstring(ObjName->text()) + ".scene", 
			glm::vec3(theModel->lightPosition.x, theModel->lightPosition.y, theModel->lightPosition.z));
		SceneMaker::makeScene(getStringFromQstring(getFileLocationLabel->text()), getStringFromQstring(ObjName->text()) + ".scene", svf);
		theModel->resendData = true;
	}
	else
	{
		svf = 1;
		checkboxColor->show();
		checkboxTexture->show();
		checkboxNormals->show();
		ObjName->show();
		getFileLocation->show();
		getFileLocationLabel->show();
		getTextureLocation->show();
		getTextureLocationLabel->show();
		save->setText("Done");
		
	}
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
