#pragma once
#pragma warning(push)
#pragma warning (disable:4251)
#pragma warning (disable:4127)
#include "QtGui\qboxlayout.h"
#pragma warning(pop)
#include <QtGui\qpushbutton.h>
#include <Qt\qframe.h>
#define MAX_OBJS 500

class Hierarchy :
	public QVBoxLayout
{
	Q_OBJECT
public:
	Hierarchy();
	~Hierarchy();

public:
	void Initialize();
	void SetHidden(bool);

	inline bool IsHidden() { return isHidden; }
	inline QFrame* GetWidget() { return frame; }

protected:

private:
	QFrame* frame;
	QPushButton* objectsInScene[MAX_OBJS];

	bool isHidden;
};

