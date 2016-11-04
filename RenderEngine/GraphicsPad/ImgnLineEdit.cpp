#include "ImgnLineEdit.h"
#include "ImgnComponent.h"
#include "Qt/qvalidator.h"

ImgnLineEdit::ImgnLineEdit()
{
}


ImgnLineEdit::ImgnLineEdit(std::string currentText, Imgn::VecPart xyz, ImgnComponent* parent) : QLineEdit(currentText.c_str()) , isX(false), isY(false), isZ(false)
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

ImgnLineEdit::ImgnLineEdit(std::string currentText, ImgnComponent* parent) : QLineEdit(currentText.c_str()) , isX(false), isY(false), isZ(false)
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
	this->selectAll();
	QLineEdit::focusInEvent(e);
	parentWidget->focusInEvent(e);
}
