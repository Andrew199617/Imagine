#include "ImgnLineEdit.h"
#include "ImgnComponent.h"
#include "Qt/qvalidator.h"

ImgnLineEdit::ImgnLineEdit()
{
}


ImgnLineEdit::ImgnLineEdit(std::string currentText, Imgn::VecPart xyz, ImgnComponent* parent) : QLineEdit(currentText.c_str()) , isX(false), isY(false), isZ(false), m_SelectAll(0)
{
	parentWidget = parent;
	switch (xyz)
	{
	case Imgn::ISX:
		isX = true;
		break;
	case Imgn::ISY:
		isY = true;
		break;
	case Imgn::ISZ:
		isZ = true;
		break;
	}
	setFocusPolicy(Qt::ClickFocus);
	QDoubleValidator* validator = new QDoubleValidator;
	setValidator(validator);
}

ImgnLineEdit::ImgnLineEdit(std::string currentText, ImgnComponent* parent) : QLineEdit(currentText.c_str()) , isX(false), isY(false), isZ(false), m_SelectAll(0)
{
	parentWidget = parent;
	setFocusPolicy(Qt::ClickFocus);
}

ImgnLineEdit::~ImgnLineEdit()
{
}

void ImgnLineEdit::focusOutEvent(QFocusEvent * e)
{
	QLineEdit::focusOutEvent(e);
	parentWidget->focusOutEvent(e);
}

void ImgnLineEdit::focusInEvent(QFocusEvent * e)
{
	QLineEdit::focusInEvent(e);
	m_SelectAll = true;
	parentWidget->focusInEvent(e);
}

void ImgnLineEdit::mousePressEvent(QMouseEvent *me)
{
	QLineEdit::mousePressEvent(me);
	if (m_SelectAll)
	{
		selectAll();
		m_SelectAll = false;
	}
}
