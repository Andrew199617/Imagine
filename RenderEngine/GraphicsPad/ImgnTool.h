#pragma once
#include "ImgnFrame.h"
class QPushButton;
class QMenu;
class QHBoxLayout;

class ImgnTool :
	public ImgnFrame
{
public:
	ImgnTool();
	//tool must have an icon that is 25/25
	ImgnTool(QPushButton* tool, QPushButton* ExtraOptions = 0);
	~ImgnTool();

	// Inherited via ImgnFrame
	virtual void Initialize() override;

	void setTool(QPushButton* button) { tool = button; }
	void SetQssFile();
private:
	QHBoxLayout* m_Layout;
	QPushButton* tool;
	QPushButton* extraOptions;
	QMenu* options;
};

