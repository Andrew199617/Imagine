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



MeWidget::MeWidget(MeGlWindow* meGl, MeModel* model)
{
	SaveLogger::intialize();
	theModel = model;
	this->meGlWindow = meGl;
	QVBoxLayout* mainLayout;
	setLayout(mainLayout = new QVBoxLayout);
	mainLayout->addLayout(controlsLayout = new QVBoxLayout);
	mainLayout->addWidget(meGlWindow);
	controlsLayout->addWidget(uD = new DebugSlider("Rotation: ", 0.0f, 360.0f, true, 36));
	controlsLayout->addWidget(uR = new DebugSlider("Offset From Mid: ", 0.0f, 1.0f, true, 10));
	uD->setFixedHeight(50);
	uD->setValue(10.f);
	uR->setFixedHeight(50);
	uR->setValue(1.f);
	theModel->uD = uD->value();
	theModel->uR = uR->value();

	connect(uD, SIGNAL(valueChanged(float)), this, SLOT(sliderValueChanged()));
	connect(uR, SIGNAL(valueChanged(float)), this, SLOT(sliderValueChanged()));
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
	QString obj = QString::fromStdString(str);
	getFileLocationLabel->setText(obj);
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