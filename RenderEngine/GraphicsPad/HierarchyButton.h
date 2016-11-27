#pragma once
#include "ImgnButton.h"
class QHBoxLayout;
class HierarchyButton :
	public ImgnButton
{
	Q_OBJECT
public:
	HierarchyButton(std::string Text);
	~HierarchyButton();

	void Initialize();
	void SetAsActiveButton();

	void SetCurPressedButton(HierarchyButton* val) { curPressedButton = val; }
protected:
	virtual void mousePressEvent(QMouseEvent *) override;

private slots:
	void ViewablePressed();

private:
	static HierarchyButton* curPressedButton;
	QHBoxLayout* m_Layout;
	QPushButton* isViewable;
};

