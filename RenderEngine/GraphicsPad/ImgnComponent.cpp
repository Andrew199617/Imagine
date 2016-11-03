#include "ImgnComponent.h"
#include "Qt\qlabel.h"
#include "Qt\qlineedit.h"
#include "Qt\qcheckbox.h"
#include "glm.hpp"
#include "ImgnProperties.h"
#include "Qt\qboxlayout.h"

#define ADDQLINEEDIT(type) if (name == typeid(type*).name()) \
{ \
	QLineEdit* lineEdit = new QLineEdit(std::to_string(*static_cast<type*>(displayData->values[i])).c_str()); \
	lineEdit->setObjectName(std::to_string(i).c_str()); \
	properties[i]->addWidget(lineEdit); \
	connect(lineEdit, SIGNAL(returnPressed()), this, SLOT(LineEdited())); \
} \

#define UPDATEQLINEEDIT(type, Type) if (name == typeid(type*).name()) \
{ \
	type* val = reinterpret_cast<type*>(displayData->values[i]); \
	*val = lineEdit->text().##Type; \
} \

ImgnComponent::ImgnComponent()
{
	componentType = -1;
	layoutInitalized = false;
	layoutHasData = false; 
	isHidden = true;
	m_owner = 0;
	displayData = 0;
}


ImgnComponent::~ImgnComponent()
{
	if (displayData)
	{
		delete displayData;
	}
}

bool ImgnComponent::Init()
{
	m_enabled = true;
	SetSaved(true);
	bool result = Initialize();
	if (!result)
	{
		string s = ": failed to initialize";
		GameLogger::log(this->GetName() + s);
	}
	return result;
}

Imgn::DisplayData* ImgnComponent::GetDisplayData()
{
	if (displayData && displayData->hasData) return displayData; 
	else return 0;
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

void ImgnComponent::AwakeSuper()
{
	displayData = Imgn::ImgnProperties::Instance()->GetMyProperties<decltype(this)>(componentType, componentTypeNum);
	Awake();
}

void ImgnComponent::DisplayInEngine()
{
	if (!isHidden && componentType != -1)
	{
		if (displayData && displayData->hasData)
		{
			m_Layout = new QVBoxLayout;
			m_Layout->addSpacing(12);
			for (int i = 0; i < displayData->numValues; i++)
			{
				properties[i] = new QHBoxLayout();
				properties[i]->addWidget(propertyNames[i] = new QLabel(displayData->variableNames[i].c_str()));

				const char* name = displayData->typeName[i];

				ADDQLINEEDIT(float)
				else ADDQLINEEDIT(int)
				else ADDQLINEEDIT(double)
				else ADDQLINEEDIT(long)
				//else ADDQLINEEDIT(char)
				else ADDQLINEEDIT(short)
				else ADDQLINEEDIT(unsigned int)
				//else ADDQLINEEDIT(unsigned char)
				else if (name == typeid(string*).name())
				{
					QLineEdit* lineEdit = new QLineEdit((*static_cast<string*>(displayData->values[i])).c_str());
					lineEdit->setObjectName(std::to_string(i).c_str());
					properties[i]->addWidget(lineEdit); 
					connect(lineEdit, SIGNAL(returnPressed()), this, SLOT(LineEdited())); 
				}
				else if (name == typeid(char**).name())
				{
					QLineEdit* lineEdit = new QLineEdit((*static_cast<char**>(displayData->values[i])));
					lineEdit->setObjectName(std::to_string(i).c_str());
					properties[i]->addWidget(lineEdit);
					connect(lineEdit, SIGNAL(returnPressed()), this, SLOT(LineEdited()));
				}
				else if (name == typeid(bool*).name())
				{
					QCheckBox* checkBox = new QCheckBox();
					checkBox->setChecked(*(static_cast<bool*>(displayData->values[i])));
					checkBox->setObjectName(("Bool" + std::to_string(i)).c_str());
					properties[i]->addWidget(checkBox);
					connect(checkBox, SIGNAL(released()), this, SLOT(LineEdited()));
				}
				else if (name == typeid(glm::vec3*).name())
				{
					glm::vec3* vec = static_cast<glm::vec3*>(displayData->values[i]);

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

void ImgnComponent::LineEdited()
{
	QObject* sender = QObject::sender();
	string objectName = sender->objectName().toLocal8Bit().constData();

	for (int i = 0; i < displayData->numValues; i++)
	{
		if (objectName == std::to_string(i))
		{
			const char* name = displayData->typeName[i];
			QLineEdit* lineEdit = reinterpret_cast<QLineEdit*>(sender);
			UPDATEQLINEEDIT(int, toInt())
			else UPDATEQLINEEDIT(float, toFloat())
			else UPDATEQLINEEDIT(double, toDouble())
			else UPDATEQLINEEDIT(char*, toLocal8Bit().data())
			else UPDATEQLINEEDIT(long, toLong())
			else UPDATEQLINEEDIT(short, toShort())
			else UPDATEQLINEEDIT(unsigned int, toUInt())
			SetSaved(false);
		}
		if (objectName == "Bool" + std::to_string(i))
		{
			QCheckBox* checkBox = reinterpret_cast<QCheckBox*>(sender);
			bool* val = reinterpret_cast<bool*>(displayData->values[i]);
			*val = checkBox->isChecked();
			SetSaved(false);
		}
	}
}
