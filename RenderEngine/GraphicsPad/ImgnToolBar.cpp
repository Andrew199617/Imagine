#include "ImgnToolBar.h"
#include "ImgnTool.h"
#include "Qt\qboxlayout.h"
#include "Qt\qpushbutton.h"
#include "DetailsLayout.h"
#include <fstream>
//"\\CSS\\ImgnTool.qss"
using std::string;

ImgnToolBar::ImgnToolBar()
{
	Initialize();
}


ImgnToolBar::~ImgnToolBar()
{
}

void ImgnToolBar::Initialize()
{
	currentTool = 0;
	m_Layout = new QHBoxLayout;
	m_Layout->setSpacing(0);
	m_Layout->setContentsMargins(0, 0, 0, 0);
	setLayout(m_Layout);
	SetQssFile("\\CSS\\ImgnToolBar.qss");

	buttons[Imgn::COMPILE_BUTTON] = new QPushButton("C");
	AddTool(new ImgnTool(buttons[Imgn::COMPILE_BUTTON]));
	connect(buttons[Imgn::COMPILE_BUTTON], SIGNAL(pressed()), this, SLOT(Compile()));
	
	//should calculate width depending on if buttons have ExtraOptions.
	this->setFixedSize(Imgn::NUM_TOOLS * 79,55);
}

void ImgnToolBar::AddTool(ImgnTool * Tool)
{
	tools[currentTool] = Tool;
	tools[currentTool]->setParent(this);
	m_Layout->addWidget(tools[currentTool], 0, Qt::AlignLeft | Qt::AlignJustify);
	currentTool++;
}

void ImgnToolBar::Compile()
{

	DetailsLayout::Instance()->CreateMenu();
}

std::string ImgnToolBar::classesToCompile[] = { "" };
