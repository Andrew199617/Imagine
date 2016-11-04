#pragma once
#include "Qt/qlineedit.h"
#include "glm.hpp"
class ImgnComponent;
namespace Imgn
{
	enum VecPart
	{
		ISX,
		ISY,
		ISZ
	};
}

class ImgnLineEdit : public QLineEdit
{

	ImgnLineEdit();
public:
	ImgnLineEdit(std::string currentText, ImgnComponent* parent);
	ImgnLineEdit(std::string currentText, Imgn::VecPart xyz, ImgnComponent* parent);
	~ImgnLineEdit();

	bool IsX() const { return isX; }
	bool IsY() const { return isY; }
	bool IsZ() const { return isZ; }
private:
	bool isVec3;
	bool isX;
	bool isY;
	bool isZ;

	ImgnComponent* parentWidget;
protected:
	void focusOutEvent(QFocusEvent *) override;


	virtual void focusInEvent(QFocusEvent *) override;

};

