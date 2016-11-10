#pragma once
#include "ImgnFrame.h"
class QVBoxLayout;
class QHBoxLayout;
class ImgnFolder;
class CBDirectory;

namespace Imgn
{
	enum
	{
		MAX_FILES_COLUMN = 6,
	};
}

class ContentBrowser :
	public ImgnFrame
{
public:
	ContentBrowser();
	~ContentBrowser();
protected:
	void Initialize() override;

private:
	QHBoxLayout* m_Layout;
	CBDirectory* directory;
	QVBoxLayout* filesHolder;
	QHBoxLayout* files[Imgn::MAX_FILES_COLUMN];

	std::string fileLocation;

};

