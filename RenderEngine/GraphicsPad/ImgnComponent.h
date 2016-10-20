#pragma once
#include "Component.h"
#include "Entity.h"
#include "Qt\qgroupbox.h"
class QLabel;
class QVBoxLayout;
class QHBoxLayout;


class ImgnComponent :
	public QGroupBox, public Component
{
public:
	ImgnComponent();
	~ImgnComponent();

public:
	//Called in constructer, Use to initialize variables.
	virtual void Awake() {}
	//You can use components from other classes
	virtual bool Initialize() { return true; }
	//Called every frame.
	virtual bool Update(float) { return true; }
	virtual bool Draw() { return true; }

	void SetOwner(Imgn::Entity* owner) { m_owner = owner; }
	Imgn::Entity* GetOwner() { return m_owner; }

	virtual void CreateWidgets();
	virtual void ClearFocus() {}
	virtual void SetHidden(bool IsHidden) { isHidden = IsHidden; }
	inline bool GetHidden() { return isHidden; }
	virtual void DeleteWidgets();

	bool layoutHasData;
	bool layoutInitalized;
protected:
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

private:
	int componentType;
	int componentTypeNum;
	QHBoxLayout* properties[Imgn::MAX_VARIABLES];
	QLabel* propertyNames[Imgn::MAX_VARIABLES];
	int numProp;
	
};