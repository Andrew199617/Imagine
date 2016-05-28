#pragma warning(push)
#pragma warning (disable:4127)
#include <QtGui\qwidget.h>
#pragma warning(pop)
#pragma warning(push)
#pragma warning (disable:4127)
#include <Qt\qapplication.h>
#pragma warning(pop)
#include "MeWidget.h"
#include "OriginalGame.h"
#include "MeGlWindow.h"
#include "ConfigReader.h"
#include "GameLogger.h"
#include "NoiseGenerator.h"

int main(int argc, char* argv[])
{

	QApplication app(argc, argv);

	GameLogger::intialize();
	ConfigReader::Initialize();
	OriginalGame game;
	MeGlWindow *window = new MeGlWindow(&app, &game);
	MeWidget meWidget(window, game.getModel());
	meWidget.showMaximized();
	return app.exec();
}

//void main()
//{
//	NoiseGenerator noiseGenerator;
//	noiseGenerator.writeImage("Tester");
//}