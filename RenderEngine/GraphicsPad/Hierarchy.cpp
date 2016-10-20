#include "Hierarchy.h"
#include "OriginalGame.h"
#pragma warning(push)
#pragma warning (disable:4127)
#include "QtGui\qboxlayout.h"
#pragma warning(pop)
#include "Qt\qpushbutton.h"

Hierarchy::Hierarchy()
{
	Initialize();
}


Hierarchy::~Hierarchy()
{
}

void Hierarchy::Initialize()
{
	isHidden = false;

	m_Layout = new QVBoxLayout();
	setLayout(m_Layout);

	setFrameShape(QFrame::Shape::Box);
	setFrameShadow(QFrame::Shadow::Sunken);
	setLineWidth(2);
	setObjectName("Hierarchy");

	/*QPalette palette = this->palette();
	palette.setColor(backgroundRole(), QColor(224, 255, 255));
	setPalette(palette);
	setAutoFillBackground(true);*/
	setStyleSheet("QFrame#Hierarchy { background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: .5, stop: 0 rgb(224,255,255), stop: .5 rgb(214,250,255));"
	"background: qlineargradient(x1: 0, y1: .5, x2: 0, y2: 1, stop: .5 rgb(204, 245, 255), stop: 1 rgb(194, 240, 255)); }" );

	for (int i = 0; i < OriginalGame::entityManager.num_Objs; i++)
	{
		m_Layout->addWidget(objectsInScene[i] = new QPushButton(OriginalGame::entityManager.entities[i].GetName()));
	}

	m_Layout->insertStretch(-1, 1);
}

void Hierarchy::SetHidden(bool b)
{
	isHidden = b;
	setHidden(b);
	for (int i = 0; i < OriginalGame::entityManager.num_Objs; i++)
	{
		objectsInScene[i]->setHidden(b);
	}
}
