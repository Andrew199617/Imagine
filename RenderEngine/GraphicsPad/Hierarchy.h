#pragma once
#include "ImgnFrame.h"
class QPushButton;
class QVBoxLayout;
#define MAX_OBJS 500

class Hierarchy :
	public ImgnFrame
{
	Q_OBJECT
public:
	Hierarchy();
	~Hierarchy();

public:
	void Initialize();
	void SetHidden(bool);

	inline bool IsHidden() { return isHidden; }
	inline QFrame* GetWidget() { return this; }

protected:
private:
	QVBoxLayout* m_Layout;
	QPushButton* objectsInScene[MAX_OBJS];

	bool isHidden;
};

