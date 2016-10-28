#pragma once
#include "Component.h"
#include "Entity.h"
#include "Qt\qgroupbox.h"
class QLabel;
class QVBoxLayout;
class QHBoxLayout;
namespace Imgn { struct DisplayData; }


class ImgnComponent :
	public QGroupBox, public Component
{
	Q_OBJECT
public:
	ImgnComponent();
	~ImgnComponent();

public:
	
	//Called every frame.
	virtual bool Update(float) { return true; }
	virtual bool Draw() { return true; }
	Imgn::DisplayData* GetDisplayData() { return displayData; }

	void SetOwner(Imgn::Entity* owner) { m_owner = owner; }
	Imgn::Entity* GetOwner() { return m_owner; }

	virtual void CreateWidgets();
	virtual void ClearFocus() {}
	//have implementation be public.
	virtual void SetHidden(bool IsHidden) { isHidden = IsHidden; }
	inline bool GetHidden() { return isHidden; }
	virtual void DeleteWidgets();

	bool layoutHasData;
	bool layoutInitalized;
protected:
	//Called in constructer, Use to initialize variables.
	virtual void Awake() {}
	//You can use components from other classes
	virtual bool Initialize() { return true; }

	void SetComponentType(int i) { componentType = i; }
	void SetComponentTypeNum(int i) { componentTypeNum = i; }
	template <class T> T* GetSiblingComponent()
	{
		return m_owner->GetComponentByType<T>();
	}

protected:
	QVBoxLayout* m_Layout;
	Imgn::Entity* m_owner;
	bool isHidden;

private:
	void DisplayInEngine();
	virtual void SetSaved_Implentation(bool val) override { m_owner->SetSaved(val); }

private slots:
	void LineEdited();

private:
	Imgn::DisplayData* displayData;

	int componentType;
	int componentTypeNum;

	//holds the data that will be displayed in the editor
	QHBoxLayout* properties[Imgn::MAX_VARIABLES];
	QLabel* propertyNames[Imgn::MAX_VARIABLES];
	int numProp;

	
};