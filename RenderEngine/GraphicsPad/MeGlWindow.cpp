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
#include "Qt\qtooltip.h"
#include "glm.hpp"
#include "gtx\transform.hpp"

void MeGlWindow::Initialize()
{
	if (!game->Initialize())
	{
		GameLogger::shutdownLog();
		app->exit();
		ShutdownApp = true;
	}
}

void MeGlWindow::initializeGL()
{
	setFocus();
	game->InitializeGl();
	setMouseTracking(true);
	setMinimumSize(1280, 720);

	connect(&myTimer, SIGNAL(timeout()),
		this, SLOT(myUpdate()));
	myTimer.start(0);
}

void MeGlWindow::mouseMoveEvent(QMouseEvent* e)
{
	QWidget::mouseMoveEvent(e);
	game->ProcessMouseMove(e);
}

void MeGlWindow::mousePressEvent(QMouseEvent * e)
{
	QWidget::mousePressEvent(e);
	setFocus();
	game->ProcessMousePress(e);
}

void MeGlWindow::resizeGL(int w, int h)
{
	QGLWidget::resizeGL(w,h);
	game->SetWidth(w);
	game->SetHeight(h);
	glm::mat4 projectionMatrix = glm::perspective(90.0f, ((float)w) / h, 1.0f, 180.0f);
	TransformInfo::projectionMatrix = projectionMatrix;
}

void MeGlWindow::myUpdate()
{	
	game->Update(hasFocus());
	if(hasFocus())
		shutdown();
	if (!ShutdownApp)
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
	Initialize();
}

void MeGlWindow::shutdown()
{
	if (GetAsyncKeyState(88) & 0x8000 || GetAsyncKeyState(27) & 0x8000)
	{
		if (SaveLogger::Instance()->shutdownLog())
		{
			GameLogger::shutdownLog();
			app->exit();
			ShutdownApp = true;
		}
	}
}

bool MeGlWindow::forceShutdown()
{
	if (SaveLogger::Instance()->shutdownLog())
	{
		GameLogger::shutdownLog();
		app->exit();
		ShutdownApp = true;
		return true;
	}
	return false;
}
