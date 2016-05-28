#include <gl\glew.h>
#include "MeGlWindow.h"
#pragma warning(push)
#pragma warning (disable:4251)
#pragma warning (disable:4127)
#include <QtGui\qmouseevent>
#pragma warning(pop)
#include "OriginalGame.h"
#include "SaveLogger.h"
#include "GameLogger.h"


void MeGlWindow::initializeGL()
{
	setMinimumSize(1280, 720);
	setMouseTracking(true);
	game->Initialize(this);

	connect(&myTimer, SIGNAL(timeout()),
		this, SLOT(myUpdate()));
	myTimer.start(0);

}

void MeGlWindow::mouseMoveEvent(QMouseEvent* e)
{
	game->ProcessMouse(e);
}

void MeGlWindow::myUpdate()
{
	game->Update();
	if(!ShutdownApp)
	repaint();
}

MeGlWindow::MeGlWindow()
{

}

MeGlWindow::MeGlWindow(QApplication* app, OriginalGame* ocGame)
{
	this->app = app;
	this->game = ocGame;
	ShutdownApp = false;
}

void MeGlWindow::shutdown()
{
	SaveLogger::shutdownLog();
	GameLogger::shutdownLog();
	app->exit();
	ShutdownApp = true;
}