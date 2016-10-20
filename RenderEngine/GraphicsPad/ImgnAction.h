#pragma once
#include "QtGui\qaction.h"

class ImgnAction :
	public QAction
{
public:
	ImgnAction(const QString &text, QObject* parent);
	ImgnAction(const QIcon &icon, const QString &text, QObject* parent);
	~ImgnAction();
	
	template <class T> void Create()
	{
		t = new T();
	}
	void* t;

};
