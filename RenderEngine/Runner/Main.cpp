#pragma warning(push)
#pragma warning (disable:4127)
#include <Qt\qapplication.h>
#pragma warning(pop)
#include "ImgnMainWindow.h"
#include "ImgnViewport.h"
#include "MeGlWindow.h"
#include "GameLogger.h"


int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	GameLogger::Intialize();
	ImgnViewport game;
	MeGlWindow *window = new MeGlWindow(&app, &game);
	ImgnMainWindow meWidget(window);
	meWidget.showMaximized();
	return app.exec();
}