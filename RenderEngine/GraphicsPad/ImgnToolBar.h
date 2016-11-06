#pragma once
#include "ImgnFrame.h"
#include "EntityData.h"
#include <string>
class ImgnTool;
class QHBoxLayout;
class QPushButton;
class QMenu;
namespace Imgn
{
	const int MAX_TOOLS = 15;
	enum
	{
		PLAY_BUTTON = 0,
		COMPILE_BUTTON = 1,
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
	void SetQssFile();

	static std::string classesToCompile[Imgn::MAX_COMPONENTS_PERENTITY];
private slots:
	void Compile();

private:
	QHBoxLayout* m_Layout;
	ImgnTool* tools[Imgn::MAX_TOOLS];
	QPushButton* buttons[Imgn::MAX_TOOLS];
	QMenu* buttonOptions[Imgn::MAX_TOOLS];

	int currentTool;
};

