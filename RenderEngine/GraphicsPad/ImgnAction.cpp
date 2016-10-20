#include "ImgnAction.h"

ImgnAction::ImgnAction(const QString & text, QObject * parent) : QAction(text,parent)
{
}

ImgnAction::ImgnAction(const QIcon & icon, const QString & text, QObject * parent) : QAction(icon,text, parent)
{
}

ImgnAction::~ImgnAction()
{
}

