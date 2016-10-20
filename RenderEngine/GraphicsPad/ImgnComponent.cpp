#include "ImgnComponent.h"
#include "Qt\qlabel.h"
#include "Qt\qlineedit.h"
#include "Qt\qcheckbox.h"
#include "glm.hpp"
#include "ImgnProperties.h"
#include "Qt\qboxlayout.h"

#define ADDQLINEEDIT(type) else if (name == typeid(type*).name()) \
{ \
	properties[i]->addWidget(new QLineEdit(std::to_string(*static_cast<float*>(displayData.values[i])).c_str())); \
} \

ImgnComponent::ImgnComponent()
{
	componentType = -1;
	layoutInitalized = false;
	layoutHasData = false; 
	isHidden = true;
	m_owner = 0;
	
}


ImgnComponent::~ImgnComponent()
{
}

void ImgnComponent::CreateWidgets()
{
	DisplayInEngine();
	setTitle(m_name);
	layoutInitalized = true;
}

void ImgnComponent::DeleteWidgets()
{
}

void ImgnComponent::DisplayInEngine()
{
	if (!isHidden && componentType != -1)
	{
		Imgn::ImgnProperties* imgnProperties = Imgn::ImgnProperties::Instance();
		Imgn::DisplayData displayData = imgnProperties->HasProperties<decltype(this)>(componentType,componentTypeNum);
		if (displayData.hasData)
		{
			m_Layout = new QVBoxLayout;
			m_Layout->addSpacing(12);
			for (int i = 0; i < displayData.numValues; i++)
			{
				properties[i] = new QHBoxLayout();
				properties[i]->addWidget(propertyNames[i] = new QLabel(displayData.variableNames[i].c_str()));

				const char* name = displayData.typeName[i];
				if (name == typeid(float*).name())
				{
					properties[i]->addWidget(new QLineEdit(std::to_string(*static_cast<float*>(displayData.values[i])).c_str()));
				}
				ADDQLINEEDIT(int)
				ADDQLINEEDIT(double)
				ADDQLINEEDIT(string)
				ADDQLINEEDIT(char)
				ADDQLINEEDIT(const char)
				if (name == typeid(bool*).name())
				{
					properties[i]->addWidget(new QCheckBox);
				}
				if (name == typeid(glm::vec3*).name())
				{
					glm::vec3* vec = static_cast<glm::vec3*>(displayData.values[i]);

					properties[i]->addWidget(new QLineEdit(std::to_string(vec->x).c_str()));
					properties[i]->addWidget(new QLineEdit(std::to_string(vec->y).c_str()));
					properties[i]->addWidget(new QLineEdit(std::to_string(vec->z).c_str()));
				}
				properties[i]->insertStretch(-1, 1);
				m_Layout->addLayout(properties[i]);
			}

			m_Layout->insertStretch(-1, 1);
			m_Layout->sizeHint().setHeight(50);
			m_Layout->minimumSize().setHeight(50);
			setLayout(m_Layout);
			layoutHasData = true;
		}
	}
}
