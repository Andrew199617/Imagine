#include "Hierarchy.h"
#include "OriginalGame.h"

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
	frame = new QFrame;
	frame->setLayout(this);
	frame->setFrameShape(QFrame::Shape::Box);
	frame->setFrameShadow(QFrame::Shadow::Sunken);
	frame->setLineWidth(2);
	QPalette palette = frame->palette();
	palette.setColor(frame->backgroundRole(), QColor(224, 255, 255));
	frame->setPalette(palette);
	frame->setAutoFillBackground(true);

	for (int i = 0; i < OriginalGame::entityManager.num_Objs; i++)
	{
		this->addWidget(objectsInScene[i] = new QPushButton(OriginalGame::entityManager.entities[i].GetName()));
	}

	this->insertStretch(-1, 1);
}

void Hierarchy::SetHidden(bool b)
{
	isHidden = b;
	frame->setHidden(b);
	for (int i = 0; i < OriginalGame::entityManager.num_Objs; i++)
	{
		objectsInScene[i]->setHidden(b);
	}
}
