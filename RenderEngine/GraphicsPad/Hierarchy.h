#pragma once
#include "ImgnFrame.h"
#include "Entity.h"
class HierarchyButton;
class QVBoxLayout;
class ImgnLabel;
#define MAX_OBJS 500

class Hierarchy : public ImgnFrame
{
	Q_OBJECT

private:
	Hierarchy();
public:
	~Hierarchy();

	void SetEntity(std::string name);
	void RemoveEntity(const char * EntityName);
public:
	static Hierarchy* Instance() { if (!instance) instance = new Hierarchy; return instance; }
	void Initialize();
	void SetHidden(bool);

	inline bool IsHidden() { return isHidden; }

private slots:
	void OnObjectPressed();

protected:
private:
	static Hierarchy* instance;

	ImgnLabel* label;
	QVBoxLayout* m_Layout;
	HierarchyButton* objectsInScene[MAX_OBJS];

	bool isHidden;
public:
	void AddEntity(Imgn::Entity entities);
	void SetEntityName(Imgn::Entity* currentEntity, std::string newName);
};

