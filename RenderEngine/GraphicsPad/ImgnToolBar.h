#pragma once
#include "ImgnFrame.h"
#include "EntityData.h"
class ImgnTool;
class QHBoxLayout;
class QPushButton;
class QMenu;
namespace Imgn
{
	enum
	{
		PLAY_BUTTON = 0,
		COMPILE_BUTTON = 1,
		NUM_TOOLS
	};
}

class ImgnToolBar :
	public ImgnFrame
{
	Q_OBJECT
public:
	ImgnToolBar();
	~ImgnToolBar();
	void Initialize();
	void AddTool(ImgnTool* Tool);

	static std::string classesToCompile[Imgn::MAX_COMPONENTS_PERENTITY];
private slots:
	void Compile();

private:
	QHBoxLayout* m_Layout;
	ImgnTool* tools[Imgn::NUM_TOOLS];
	QPushButton* buttons[Imgn::NUM_TOOLS];
	QMenu* buttonOptions[Imgn::NUM_TOOLS];

	int currentTool;
};

