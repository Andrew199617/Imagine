#pragma once
#include "ImgnFrame.h"
class HierarchyButton;
class QVBoxLayout;
#define MAX_OBJS 500

class Hierarchy : public ImgnFrame
{
	Q_OBJECT

private:
	Hierarchy();
public:
	~Hierarchy();

	void SetEntity(std::string name);
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

	QVBoxLayout* m_Layout;
	HierarchyButton* objectsInScene[MAX_OBJS];

	bool isHidden;
};

