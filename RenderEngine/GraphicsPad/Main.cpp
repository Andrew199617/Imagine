#pragma warning(push)
#pragma warning (disable:4127)
#include <Qt\qapplication.h>
#pragma warning(pop)
#include "MeWidget.h"
#include "OriginalGame.h"
#include "MeGlWindow.h"
#include "GameLogger.h"


int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	GameLogger::Intialize();
	OriginalGame game;
	MeGlWindow *window = new MeGlWindow(&app, &game);
	MeWidget meWidget(window);
	meWidget.showMaximized();
	return app.exec();
}