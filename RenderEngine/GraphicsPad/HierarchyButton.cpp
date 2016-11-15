#include "HierarchyButton.h"
#include "QtGui\qevent.h"
#include "Qt\qboxlayout.h"
#include "ImgnViewport.h"


HierarchyButton* HierarchyButton::curPressedButton = 0;

HierarchyButton::HierarchyButton(std::string Text) : ImgnButton()
{
	setCheckable(true);
	setText(Text.c_str());
	Initialize();
}

HierarchyButton::~HierarchyButton()
{

}

void HierarchyButton::Initialize()
{
	setObjectName("HierarchyButton");
	setLayout(m_Layout = new QHBoxLayout);
	m_Layout->addWidget(isViewable = new QPushButton, 0, Qt::AlignLeft);
	isViewable->setCheckable(true);
	isViewable->setObjectName("VisibleButton");
	isViewable->setChecked(true);
	connect(isViewable, SIGNAL(pressed()), this, SLOT(ViewablePressed()));
}

void HierarchyButton::SetAsActiveButton()
{
	if (curPressedButton)
	{
		curPressedButton->setChecked(false);
	}
	setChecked(true);
	curPressedButton = this;
}

void HierarchyButton::mousePressEvent(QMouseEvent * event)
{
	if (curPressedButton)
	{
		curPressedButton->setChecked(false);
	}
	QWidget::mousePressEvent(event);
	setChecked(true);
	curPressedButton = this;
	emit pressed();
	
	/*if (event->button() == Qt::LeftButton && this->geometry().contains(event->pos())) {

		QDrag *drag = new QDrag(this);
		QMimeData *mimeData = new QMimeData;

		mimeData->setText("Drag");
		drag->setMimeData(mimeData);
		drag->setPixmap(QPixmap(50,50));

		Qt::DropAction dropAction = drag->exec();
	}*/
}

void HierarchyButton::ViewablePressed()
{
	Imgn::Entity* entity;
	for (int i = 0; i < ImgnViewport::entityManager.num_Objs; i++)
	{
		if (text() == ImgnViewport::entityManager.entities[i].GetName())
		{
			entity = &ImgnViewport::entityManager.entities[i];
		}
	}
	if (!isViewable->isChecked())
	{
		entity->Enable();
	}
	else
	{
		entity->Disable();
	}
	
}
