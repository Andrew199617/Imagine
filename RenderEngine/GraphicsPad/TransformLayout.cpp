#include "TransformLayout.h"
#include "OriginalGame.h"
#include "glm.hpp"

QLineEdit* TransformLayout::XYZ_TextBoxs[numXYZ] = {0};

TransformLayout::TransformLayout()
{
	Initialize();
}


TransformLayout::~TransformLayout()
{

}

void TransformLayout::Initialize()
{

	isHidden = false;
	this->addSpacing(12.5);
	SetupLabels("Position",&positionLayout, &positionLabel, 0, 1, 2);
	SetupLabels("Rotate", &rotateLayout, &rotateLabel, 3, 4, 5);
	SetupLabels("Scale", &scaleLayout, &scaleLabel, 6, 7, 8);
	SetTextBoxValues();
	this->insertStretch(-1, 1);
}

void TransformLayout::SetupLabels(string name, QHBoxLayout** layout, QLabel** nameLabel, int x, int y, int z)
{
	this->addLayout((*layout) = new QHBoxLayout);
	(*layout)->addWidget(*nameLabel = new QLabel(name.c_str()));
	(*nameLabel)->setFixedWidth(50);
	(*nameLabel)->setContentsMargins(5, 5, 15 - name.length() * 2, 5);

	(*layout)->addWidget(XYZ_Labels[x] = new QLabel("X"));
	(*layout)->addWidget(XYZ_TextBoxs[x] = new QLineEdit);
	connect(XYZ_TextBoxs[x], SIGNAL(returnPressed()), this, SLOT(XYZChanged()));

	(*layout)->addWidget(XYZ_Labels[y] = new QLabel("Y"));
	(*layout)->addWidget(XYZ_TextBoxs[y] = new QLineEdit);
	connect(XYZ_TextBoxs[y], SIGNAL(returnPressed()), this, SLOT(XYZChanged()));

	(*layout)->addWidget(XYZ_Labels[z] = new QLabel("Z"));
	(*layout)->addWidget(XYZ_TextBoxs[z] = new QLineEdit);
	connect(XYZ_TextBoxs[z], SIGNAL(returnPressed()), this, SLOT(XYZChanged()));

	/*QPalette palette = XYZ_TextBoxs[x]->palette();
	palette.setColor(XYZ_TextBoxs[x]->backgroundRole(), QColor(220, 220, 220));
	XYZ_TextBoxs[x]->setPalette(palette);
	XYZ_TextBoxs[x]->setAutoFillBackground(true);
	XYZ_TextBoxs[y]->setPalette(palette);
	XYZ_TextBoxs[y]->setAutoFillBackground(true);
	XYZ_TextBoxs[z]->setPalette(palette);
	XYZ_TextBoxs[z]->setAutoFillBackground(true);*/
}

void TransformLayout::SetTextBoxValues()
{
	glm::vec3 position = OriginalGame::entityManager.entitieSpatials[OriginalGame::entityManager.currentlySelectedObject].position;
	glm::vec3 rotate = OriginalGame::entityManager.entitieSpatials[OriginalGame::entityManager.currentlySelectedObject].GetRotate();
	glm::vec3 scale = OriginalGame::entityManager.entitieSpatials[OriginalGame::entityManager.currentlySelectedObject].GetScale();
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
		values[i] = XYZ_TextBoxs[i]->text().toFloat();
	}
}

void TransformLayout::SetMaximumSize(int Width, int Height)
{
	for (int i = 0; i < numXYZ; i++)
	{
		XYZ_TextBoxs[i]->setMaximumSize(Width,Height);
	}
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