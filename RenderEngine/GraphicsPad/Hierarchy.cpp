#include "Hierarchy.h"
#include "ImgnViewport.h"
#pragma warning(push)
#pragma warning (disable:4127)
#include "QtGui\qboxlayout.h"
#pragma warning(pop)
#include "Qt\qpushbutton.h"
#include "DetailsLayout.h"
#include "HierarchyButton.h"

Hierarchy* Hierarchy::instance = 0;

void Hierarchy::AddEntity(Imgn::Entity entities)
{
	int i = ImgnViewport::entityManager.num_Objs - 1;
	m_Layout->addWidget(objectsInScene[i] = new HierarchyButton(entities.GetName()),0 , Qt::AlignTop);
	connect(objectsInScene[i], SIGNAL(pressed()), this, SLOT(OnObjectPressed()));
	m_Layout->insertStretch(-1, 1);
}

void Hierarchy::SetEntityName(Imgn::Entity* currentEntity, std::string newName)
{
	for (int i = 0; i < ImgnViewport::entityManager.num_Objs; ++i)
	{
		if (objectsInScene[i] && objectsInScene[i]->text() == currentEntity->GetName())
		{
			objectsInScene[i]->setText(newName.c_str());
		}
	}
}

Hierarchy::Hierarchy()
{
	memset(objectsInScene, 0, sizeof(objectsInScene));
	Initialize();
}


Hierarchy::~Hierarchy()
{
}

void Hierarchy::SetEntity(std::string name)
{
	for (int i = 0; i < ImgnViewport::entityManager.num_Objs; i++)
	{
		if (objectsInScene[i] && objectsInScene[i]->text() == name.c_str())
		{
			objectsInScene[i]->SetAsActiveButton();
		}
	}
}

void Hierarchy::RemoveEntity(const char * EntityName)
{
	for (int i = 0; i < ImgnViewport::entityManager.num_Objs; ++i)
	{
		if (objectsInScene[i] && objectsInScene[i]->text() == EntityName)
		{
			objectsInScene[i]->SetCurPressedButton(0);
			m_Layout->removeWidget(objectsInScene[i]);
			delete objectsInScene[i];
			objectsInScene[i] = 0;
		}
	}
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
	SetQssFile("\\CSS\\Hierarchy.qss");

	for (int i = 0; i < ImgnViewport::entityManager.num_Objs; i++)
	{
		m_Layout->addWidget(objectsInScene[i] = new HierarchyButton(ImgnViewport::entityManager.entities[i].GetName()), 0, Qt::AlignTop);
		connect(objectsInScene[i], SIGNAL(pressed()), this, SLOT(OnObjectPressed()));
	}

	m_Layout->insertStretch(-1, 1);
}

void Hierarchy::SetHidden(bool b)
{
	isHidden = b;
	setHidden(b);
	for (int i = 0; i < ImgnViewport::entityManager.num_Objs; i++)
	{
		objectsInScene[i]->setHidden(b);
	}
}

void Hierarchy::OnObjectPressed()
{
	HierarchyButton* objectPressed = reinterpret_cast<HierarchyButton*>(QObject::sender());
	for (int i = 0; i < ImgnViewport::entityManager.num_Objs; i++)
	{
		if (objectPressed->text() == ImgnViewport::entityManager.entities[i].GetName())
		{
			if (ImgnViewport::entityManager.CurrentlySelectedObject() != i)
			{
				ImgnViewport::entityManager.SetCurrentlySelectedObject(i);
			}
			break;
		}
	}
}
