#include "ImgnCreateComponent.h"
#include "Qt\qboxlayout.h"
#include "Qt\qlabel.h"
#include "Qt\qlineedit.h"
#include "Qt\qpushbutton.h"
#include "Qt\qframe.h"
#include "Qt\qmessagebox.h"
#include <fstream>
#include <stdio.h>
#include "ImgnToolBar.h"

namespace Imgn
{
	
	ImgnCreateComponent::ImgnCreateComponent(QWidget *parent)
		: QWidget(parent)
	{
		
		meWidget = new QFrame(this);
		m_Layout = new QVBoxLayout(meWidget);

		Initialize();
		setLayout(m_Layout);

		setFocus();
		setWindowFlags((Qt::Dialog | Qt::WindowStaysOnTopHint | Qt::CustomizeWindowHint) | Qt::WindowType::WindowCloseButtonHint);
		setWindowModality(Qt::WindowModality::WindowModal);
		setAttribute(Qt::WA_DeleteOnClose);
		show();
		setFixedSize(960,540);

		setWindowTitle("Add Component");
	}
	
	
	ImgnCreateComponent::~ImgnCreateComponent()
	{
	}
	
	void ImgnCreateComponent::Initialize()
	{
		classNameLayout = new QHBoxLayout;
		buttonLayout = new QHBoxLayout;
		labels[ClassNameLabel] = new QLabel("Name");
		className = new QLineEdit();
		
		noClassName = new QMessageBox();
		noClassName->setIcon(QMessageBox::Icon::Warning);
		noClassName->setStandardButtons(QMessageBox::NoButton);
		noClassName->hide();

		classNameLayout->addWidget(labels[ClassNameLabel],Qt::AlignLeft);
		classNameLayout->addWidget(className, Qt::AlignHCenter);

		AddButtons();

		m_Layout->addLayout(classNameLayout);
		m_Layout->addWidget(noClassName);
		m_Layout->addLayout(buttonLayout);
	}

	void ImgnCreateComponent::AddButtons()
	{
		addButton = new QPushButton("Create Class");
		addButton->setFixedWidth(150);
		addButton->setStyleSheet("QPushButton:enabled { border: 1px solid black; background-color:" 
			"qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 rgb(200,255,200), stop: 1 rgb(95,235,95)); border-radius:2px; padding: 10px;}"
			"QPushButton:hover { border: 1.5px solid black; background-color:"
			"qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 rgb(180,235,180), stop: 1 rgb(95,215,95)); border-radius:3px; padding: 10px;}"
			"QPushButton {font-size: 16px; color: solid black;}");
		connect(addButton, SIGNAL(pressed()), this, SLOT(CreateClass()));
		cancelButton = new QPushButton("Cancel");
		cancelButton->setFixedWidth(150);
		cancelButton->setStyleSheet("QPushButton:enabled { border: 1px solid black; background-color:" 
			"qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 rgb(255,255,255), stop: 1 rgb(150,150,150)); border-radius:2px; padding: 10px;}"
			"QPushButton:hover { border: 1.5px solid black; background-color:"
			"qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 rgb(235,235,235), stop: 1 rgb(130,130,130)); border-radius:3px; padding: 10px;}"
			"QPushButton {font-size: 16px; color: solid black;}");
		connect(cancelButton, SIGNAL(pressed()), this, SLOT(close()));
		buttonLayout->addWidget(addButton);
		buttonLayout->addWidget(cancelButton);
		//this->setStyleSheet("QPushButton {}");
	}

	void ImgnCreateComponent::CreateClass()
	{
		std::string s = className->text().toLocal8Bit().constData();
		ImgnToolBar::classesToCompile[0] = s;
		std::ofstream outputFile(s + ".h");

		outputFile << "#pragma once" << std::endl;
		outputFile << "#include \"ImgnComponent.h\"" << std::endl;
		outputFile << "#include \"DetailsLayout.h\"" << std::endl;
		outputFile << "#include \"ImgnProperties.h\"" << std::endl << std::endl;
		outputFile << "class " << s << " :" << std::endl;
		outputFile << "	public ImgnComponent" << std::endl;
		outputFile << "{" << std::endl;
		outputFile << "	IMGN_GENERATE(" << s << ")" << std::endl;
		outputFile << "	\\\\Use IMGN_PROPERTY(var_name) to have variable appear in editor" << std::endl;
		outputFile << "	\\\\IMGN_PROPERTY(gravity, 9.8)" << std::endl;
		outputFile << "	\\\\..." << std::endl;
		outputFile << "	IMGN_END(" << s << ")" << std::endl;
		outputFile << "public:" << std::endl;
		outputFile << "};" << std::endl;

		outputFile.close(); 
		outputFile.open(s + ".cpp");

		outputFile << "#include \"" << s << ".h\"" << std::endl << std::endl;
		outputFile << s << "::~" << s << "()" << std::endl;
		outputFile << "{" << std::endl << std::endl;
		outputFile << "}" << std::endl;

		outputFile.close();
		system((s + ".h").c_str());
		system((s + ".cpp").c_str());
		this->close();
		
	}

}