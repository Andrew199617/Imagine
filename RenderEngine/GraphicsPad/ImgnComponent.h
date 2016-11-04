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
	bool Init();
	//Called every frame.
	virtual void Update(float) {}
	virtual void Draw(float) {}
	Imgn::DisplayData* GetDisplayData();

	void SetOwner(Imgn::Entity* owner) { m_owner = owner; }
	Imgn::Entity* GetOwner() { return m_owner; }

	virtual void CreateWidgets();
	virtual void ClearFocus() {}
	//have implementation be public.
	virtual void SetHidden(bool IsHidden) { isHidden = IsHidden; }
	inline bool GetHidden() { return isHidden; }
	virtual void DeleteWidgets();
	virtual void focusOutEvent(QFocusEvent *) override;
	virtual void focusInEvent(QFocusEvent *) override;

	bool layoutHasData;
	bool layoutInitalized;
protected:
	void AwakeSuper();
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

	//************************************
	// Method:    GetVariableName
	// FullName:  ImgnComponent::GetVariableName
	// Access:    protected 
	// Returns:   The name that you will use for OnValueChange.
	// Parameter: var the address of the variable whos name you want.
	//************************************
	std::string GetVariableName(void* var);
	/************************************************************************/
	/* Called whenever a variable in the editor gets changed.                                                                     
	/************************************************************************/
	virtual void OnValueChange(std::string VariableName) {}

protected:
	QVBoxLayout* m_Layout;
	Imgn::Entity* m_owner;
	bool isHidden;

private:
	void DisplayInEngine();
	void AddVec3(int i);
	void SetSaved_Implentation(bool val) override { m_owner->SetSaved(val); }

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