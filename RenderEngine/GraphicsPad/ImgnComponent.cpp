#include "ImgnComponent.h"
#include "Qt\qlabel.h"
#include "ImgnLineEdit.h"
#include "Qt\qcheckbox.h"
#include "ImgnProperties.h"
#include "Qt\qboxlayout.h"
#include <string>

#define ADDQLINEEDIT(type) if (name == typeid(type*).name()) \
{ \
	ImgnLineEdit* lineEdit = new ImgnLineEdit(std::to_string(*static_cast<type*>(displayData->values[i])),this); \
	lineEdit->setObjectName(displayData->variableNames[i].c_str()); \
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

void ImgnComponent::LoadComponentData()
{
	/*if (displayData && displayData->hasData)
	{
		for (int i = 0; i < displayData->numValues; ++i)
		{

		}
	}*/
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
	Awake(); 
	displayData = Imgn::ImgnProperties::Instance()->GetMyProperties(componentType, componentTypeNum);
}

std::string ImgnComponent::GetVariableName(void* var)
{
	if (displayData && displayData->hasData)
	for (int i = 0; i < displayData->numValues; i++)
	{
		if (displayData->values[i] == var)
		{
			return displayData->variableNames[i];
		}
	}

	return "Variable Not Found did you add it with IMGN_PROPERTY";
}

void ImgnComponent::focusOutEvent(QFocusEvent * e)
{
	QGroupBox::focusOutEvent(e);
}

void ImgnComponent::focusInEvent(QFocusEvent * e)
{
	QGroupBox::focusInEvent(e);
}

void ImgnComponent::DisplayInEngine()
{
	if (!isHidden && componentType != -1)
	{
		if (displayData && displayData->hasData)
		{
			m_Layout = new QVBoxLayout;
			m_Layout->addSpacing(15);
			m_Layout->setContentsMargins(2, 0, 8, 0);
			for (int i = 0; i < displayData->numValues; ++i)
			{
				properties[i] = new QHBoxLayout();
				properties[i]->addWidget(propertyNames[i] = new QLabel(displayData->variableNames[i].c_str()));
				propertyNames[i]->setFixedWidth(80);
				propertyNames[i]->setContentsMargins(5, 5, 15 - displayData->variableNames[i].length() * 2, 5);
				QFrame* line = new QFrame();
				line->setGeometry(QRect(0, 0, 2, 30));
				line->setFrameShape(QFrame::VLine); // Replace by VLine for vertical line
				line->setFrameShadow(QFrame::Plain);
				properties[i]->addWidget(line,0,Qt::AlignLeft);

				std::string name = displayData->typeName[i];
				
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
					ImgnLineEdit* lineEdit = new ImgnLineEdit((*static_cast<string*>(displayData->values[i])), this);
					lineEdit->setObjectName(displayData->variableNames[i].c_str());
					properties[i]->addWidget(lineEdit); 
					connect(lineEdit, SIGNAL(returnPressed()), this, SLOT(LineEdited())); 
				}
				else if (name == typeid(char**).name())
				{
					ImgnLineEdit* lineEdit = new ImgnLineEdit((*static_cast<char**>(displayData->values[i])),this);
					lineEdit->setObjectName(displayData->variableNames[i].c_str());
					properties[i]->addWidget(lineEdit);
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
					AddVec3(i);

				}
				properties[i]->insertStretch(-1, 1);
				m_Layout->addLayout(properties[i]);
			}

			m_Layout->insertStretch(-1, 1);
			m_Layout->sizeHint().setHeight(50);
			m_Layout->minimumSize().setHeight(50);
			m_Layout->addSpacing(15);
			setLayout(m_Layout);
			layoutHasData = true;
		}
	}
}

void ImgnComponent::AddVec3(int i)
{
	glm::vec3* vec = static_cast<glm::vec3*>(displayData->values[i]);
	ImgnLineEdit* lineEditX = new ImgnLineEdit(std::to_string(vec->x), Imgn::ISX, this);
	ImgnLineEdit* lineEditY = new ImgnLineEdit(std::to_string(vec->y), Imgn::ISY, this);
	ImgnLineEdit* lineEditZ = new ImgnLineEdit(std::to_string(vec->z), Imgn::ISZ, this);
	lineEditX->setObjectName(displayData->variableNames[i].c_str());
	lineEditY->setObjectName(displayData->variableNames[i].c_str());
	lineEditZ->setObjectName(displayData->variableNames[i].c_str());
	properties[i]->addWidget(lineEditX);
	properties[i]->addWidget(lineEditY);
	properties[i]->addWidget(lineEditZ);
	connect(lineEditX, SIGNAL(returnPressed()), this, SLOT(LineEdited()));
	connect(lineEditY, SIGNAL(returnPressed()), this, SLOT(LineEdited()));
	connect(lineEditZ, SIGNAL(returnPressed()), this, SLOT(LineEdited()));
}

void ImgnComponent::LineEdited()
{
	QObject* sender = QObject::sender();
	
	string objectName = sender->objectName().toLocal8Bit().constData();

	for (int i = 0; i < displayData->numValues; i++)
	{
		if (objectName == displayData->variableNames[i])
		{
			std::string name = displayData->typeName[i];
			ImgnLineEdit* lineEdit = reinterpret_cast<ImgnLineEdit*>(sender);
			UPDATEQLINEEDIT(int, toInt())
			else UPDATEQLINEEDIT(float, toFloat())
			else UPDATEQLINEEDIT(double, toDouble())
			else UPDATEQLINEEDIT(char*, toLocal8Bit().data())
			else UPDATEQLINEEDIT(long, toLong())
			else UPDATEQLINEEDIT(short, toShort())
			else UPDATEQLINEEDIT(unsigned int, toUInt())
			else if (name == typeid(glm::vec3*).name()) 
			{ 
				glm::vec3* val = reinterpret_cast<glm::vec3*>(displayData->values[i]);
				if (lineEdit->IsX())
				{
					val->x = lineEdit->text().toFloat();
				}
				else if (lineEdit->IsY())
				{
					val->y = lineEdit->text().toFloat();
				}
				else if (lineEdit->IsZ())
				{
					val->z = lineEdit->text().toFloat();
				}
			} 
			SetSaved(false);
		}
		else if (objectName == "Bool" + std::to_string(i))
		{
			QCheckBox* checkBox = reinterpret_cast<QCheckBox*>(sender);
			bool* val = reinterpret_cast<bool*>(displayData->values[i]);
			*val = checkBox->isChecked();
			SetSaved(false);
		}
	}
	OnValueChange(objectName);
}
