#include "TransformLayout.h"
#include "OriginalGame.h"
#include "glm.hpp"
#include "Qt\qboxlayout.h"
#include "Qt\qlabel.h"
#include "Qt\qlineedit.h"

TransformLayout::TransformLayout()
{

}

TransformLayout::~TransformLayout()
{

}

bool TransformLayout::Initialize()
{
	isHidden = false;
	return true;
}

void TransformLayout::CreateWidgets()
{
	setTitle(m_name);
	m_Layout = new QVBoxLayout;
	m_Layout->addSpacing(12);

	SetupLabels("Position", &positionLayout, &positionLabel, 0, 1, 2);
	SetupLabels("Rotate", &rotateLayout, &rotateLabel, 3, 4, 5);
	SetupLabels("Scale", &scaleLayout, &scaleLabel, 6, 7, 8);
	SetTextBoxValues();
	m_Layout->insertStretch(-1, 1);
	setLayout(m_Layout);
	setFixedHeight(125);

	layoutHasData = true;
	layoutInitalized = true;
}

void TransformLayout::SetupLabels(string name, QHBoxLayout** layout, QLabel** nameLabel, int x, int y, int z)
{
	m_Layout->addItem((*layout) = new QHBoxLayout);
	(*layout)->addWidget(*nameLabel = new QLabel(name.c_str()));
	(*nameLabel)->setFixedWidth(50);
	(*nameLabel)->setContentsMargins(5, 5, 15 - name.length() * 2, 5);

	(*layout)->addWidget(XYZ_Labels[x] = new QLabel("X"));
	(*layout)->addWidget(XYZ_TextBoxs[x] = new QLineEdit);
	XYZ_Labels[x]->setStyleSheet("margin-right:5px;");
	connect(XYZ_TextBoxs[x], SIGNAL(returnPressed()), this, SLOT(XYZChanged()));

	(*layout)->addWidget(XYZ_Labels[y] = new QLabel("Y"));
	(*layout)->addWidget(XYZ_TextBoxs[y] = new QLineEdit);
	XYZ_Labels[y]->setStyleSheet("margin-left:5px;margin-right:5px;");
	connect(XYZ_TextBoxs[y], SIGNAL(returnPressed()), this, SLOT(XYZChanged()));

	(*layout)->addWidget(XYZ_Labels[z] = new QLabel("Z"));
	(*layout)->addWidget(XYZ_TextBoxs[z] = new QLineEdit);
	XYZ_Labels[z]->setStyleSheet("margin-left:5px;margin-right:5px;");
	connect(XYZ_TextBoxs[z], SIGNAL(returnPressed()), this, SLOT(XYZChanged()));
}

void TransformLayout::SetTextBoxValues()
{
	glm::vec3 position = OriginalGame::entityManager.entitieSpatials[OriginalGame::entityManager.currentlySelectedObject]->position;
	glm::vec3 rotate = OriginalGame::entityManager.entitieSpatials[OriginalGame::entityManager.currentlySelectedObject]->GetRotate();
	glm::vec3 scale = OriginalGame::entityManager.entitieSpatials[OriginalGame::entityManager.currentlySelectedObject]->GetScale();
	XYZ_TextBoxs[0]->setText(std::to_string(position.x).c_str());
	XYZ_TextBoxs[1]->setText(std::to_string(position.y).c_str());
	XYZ_TextBoxs[2]->setText(std::to_string(position.z).c_str());
	XYZ_TextBoxs[3]->setText(std::to_string(rotate.x).c_str());
	XYZ_TextBoxs[4]->setText(std::to_string(rotate.y).c_str());
	XYZ_TextBoxs[5]->setText(std::to_string(rotate.z).c_str());
	XYZ_TextBoxs[6]->setText(std::to_string(scale.x).c_str());
	XYZ_TextBoxs[7]->setText(std::to_string(scale.y).c_str());
	XYZ_TextBoxs[8]->setText(std::to_string(scale.z).c_str());
}

void TransformLayout::ClearFocus()
{
	for (int i = 0; i < numXYZ; i++)
	{
		XYZ_TextBoxs[i]->clearFocus();
	}
}

void TransformLayout::SetHidden(bool b)
{
	isHidden = b;
	positionLabel->setHidden(b);
	scaleLabel->setHidden(b);
	rotateLabel->setHidden(b);
	for (int i = 0; i < numXYZ; i++)
	{
		XYZ_Labels[i]->setHidden(b);
	}
	for (int i = 0; i < numXYZ; i++)
	{
		XYZ_TextBoxs[i]->setHidden(b);
	}
}

void TransformLayout::SetMaximumSize(int Width, int Height)
{
	for (int i = 0; i < numXYZ; i++)
	{
		XYZ_TextBoxs[i]->setMaximumSize(Width,Height);
	}
}

void TransformLayout::DeleteWidgets()
{	
	
}

void TransformLayout::XYZChanged()
{
	bool changed = false;
	for (int i = 0; i < numXYZ/3; i++)
	{
		if (values[i] != XYZ_TextBoxs[i]->text().toFloat())
		{
			values[i] = XYZ_TextBoxs[i]->text().toFloat();
			changed = true;
		}
	}
	if (changed)
	{
		OriginalGame::entityManager.UpdateObjectPosition(OriginalGame::entityManager.currentlySelectedObject,glm::vec3(values[0], values[1], values[2]));
		return;
	}
	for (int i = numXYZ / 3; i < (numXYZ / 3) * 2; i++)
	{
		if (values[i] != XYZ_TextBoxs[i]->text().toFloat())
		{
			values[i] = XYZ_TextBoxs[i]->text().toFloat();
			changed = true;
		}
	}
	if (changed)
	{
		OriginalGame::entityManager.UpdateObjectRotate(OriginalGame::entityManager.currentlySelectedObject, glm::vec3(values[3], values[4], values[5]));
		return;
	}
	for (int i = (numXYZ / 3) * 2; i < numXYZ; i++)
	{
		if (values[i] != XYZ_TextBoxs[i]->text().toFloat())
		{
			values[i] = XYZ_TextBoxs[i]->text().toFloat();
			changed = true;
		}
	}
	if (changed)
	{
		OriginalGame::entityManager.UpdateObjectScale(OriginalGame::entityManager.currentlySelectedObject, glm::vec3(values[6], values[7], values[8]));
		return;
	}
}