#pragma once
#include "ImgnFrame.h"
#include "ImgnFwd.hpp"
#include "ImgnAction.h"
#include "Qt\qmenu.h"
#include <string>
class QVBoxLayout;
class TransformLayout;
class QPushButton;
class ImgnComponent;
class QScrollArea;
class Entity;

class DetailsLayout :
	public ImgnFrame
{
	Q_OBJECT

	DetailsLayout();
public:
	~DetailsLayout();

	void Initialize();
	void ClearFocus();
	QVBoxLayout* m_Layout;

	void Resize();
	void SetEntity(Imgn::Entity* entity);
	void UpdateComponents();
	void AddComponent(char* name, ImgnComponent* layout,int);
	inline static DetailsLayout* Instance()
	{
		if (!detailsLayout)
			detailsLayout = new DetailsLayout;
		return detailsLayout;
	}
public:
	void CreateActions();
	void CreateMenu();
	template <class T> void CreateAction();
	template <class T> void CreateAction(std::string objectName);

private slots:
	void ButtonPressed();
	void CreateNewComponent();
	void ResizeMenu();

private:
	static DetailsLayout* detailsLayout;
	Imgn::Entity* currentEntity;

	ImgnComponent** components;
	int numComponents;

	QScrollArea* scrollArea;
	QPushButton* addComponentButton;
	Imgn::ImgnCreateComponent* createComponent;
	QAction* createNewButton;
	QMenu* componentMenu;
	ImgnAction* addableComponents[50];
	int numAddableComponenets;
	void AddEntityData(Imgn::Entity* entity);
};

template<class T> inline void DetailsLayout::CreateAction()
{
	string name = typeid(T).name();
	string objectName = name.substr(6, name.npos);
	for (unsigned i = 1; i < objectName.length(); i++)
	{
		if (isupper(objectName.at(i)))
		{
			objectName += ' ';
			for (unsigned j = objectName.length(); j > i; j--)
			{
				objectName[j] = objectName[j - 1];
			}
			objectName[i] = ' ';
			objectName += ' ';
			objectName[objectName.length() - 1] = '\0';
			i += 2;
		}
	}
	addableComponents[numAddableComponenets] = new ImgnAction(objectName.c_str(),this);
	addableComponents[numAddableComponenets]->Create<T>();
	addableComponents[numAddableComponenets]->setObjectName(objectName.c_str());
	connect(addableComponents[numAddableComponenets], SIGNAL(triggered()), this, SLOT(ButtonPressed()));
	componentMenu->addAction(addableComponents[numAddableComponenets]);
	numAddableComponenets++;
}

template<class T> inline void DetailsLayout::CreateAction(std::string objectName)
{
	addableComponents[numAddableComponenets] = new ImgnAction(objectName.c_str(), this);
	addableComponents[numAddableComponenets]->Create<T>();
	addableComponents[numAddableComponenets]->setObjectName(objectName.c_str());
	connect(addableComponents[numAddableComponenets], SIGNAL(triggered()), this, SLOT(ButtonPressed()));
	componentMenu->addAction(addableComponents[numAddableComponenets]);
	numAddableComponenets++;
}