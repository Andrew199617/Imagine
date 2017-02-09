#include <gl\glew.h>
#include "MeGlWindow.h"
#pragma warning(push)
#pragma warning (disable:4251)
#pragma warning (disable:4127)
#include <QtGui\qmouseevent>
#pragma warning(pop)
#include "ImgnViewport.h"
#include "SaveLogger.h"
#include "GameLogger.h"
#include "Qt\qtooltip.h"
#include "glm.hpp"
#include "gtx\transform.hpp"
#include "QtGui\qevent.h"
#include "Qt\qurl.h"
#include "Qt\qmainwindow.h"
#include "ImgnMimeData.h"
#include "SceneReader.h"
#include "FbxFileReader.h"
#include "ObjectSelectorComponent.h"
#include "MeshComponent.h"

void MeGlWindow::Initialize()
{
	if (!viewport->Initialize())
	{
		GameLogger::shutdownLog();
		app->exit();
		ShutdownApp = true;
	}
	setAcceptDrops(true);
}

void MeGlWindow::initializeGL()
{
	setFocus();
	viewport->InitializeGl();
	setMouseTracking(true);
	setMinimumSize(1280, 720);

	connect(&myTimer, SIGNAL(timeout()),
		this, SLOT(myUpdate()));
	myTimer.start(0);
}

void MeGlWindow::mouseMoveEvent(QMouseEvent* e)
{
	QWidget::mouseMoveEvent(e);
	viewport->ProcessMouseMove(e);
}

void MeGlWindow::mousePressEvent(QMouseEvent * e)
{
	QWidget::mousePressEvent(e);
	setFocus();
	viewport->ProcessMousePress(e);
}

void MeGlWindow::resizeGL(int w, int h)
{
	QGLWidget::resizeGL(w,h);
	viewport->SetWidth(w);
	viewport->SetHeight(h);
	glm::mat4 projectionMatrix = glm::perspective(90.0f, ((float)w) / h, 1.0f, 180.0f);
	TransformInfo::projectionMatrix = projectionMatrix;
}

void MeGlWindow::dragEnterEvent(QDragEnterEvent *event)
{
	event->setDropAction(Qt::MoveAction);
	event->accept();
	/*if (event->mimeData()->hasFormat("text/uri-list"))
		event->acceptProposedAction();*/
}

void MeGlWindow::dropEvent(QDropEvent *event)
{
	const ImgnMimeData* data = static_cast<const ImgnMimeData*>(event->mimeData());

	string fullPath = data->FilePath() + "/"+ data->FileName() + "." + data->Extension();
	if (data->Extension() == "imgnasset")
	{
		SceneReader* scenereader  = new SceneReader;
		Scene* scene = scenereader->ReadSceneFile(fullPath);
		SaveLogger::Instance()->AddObj(data->FileName());
		delete scenereader;
	}
	else if (data->Extension() == "bmp")
	{
		int objectSelected = viewport->entityManager.ObjController()->SelectObject(event->pos());
		if (objectSelected != -1)
		{
			viewport->entityManager.entitieMeshs[objectSelected]->UpdateTextureInfo(fullPath);
		}
	}
	else
	{
		return;
	}
}

void MeGlWindow::myUpdate()
{	
	viewport->Update(hasFocus());
	if(hasFocus())
		shutdown();
	if (!ShutdownApp)
		repaint();
}

MeGlWindow::MeGlWindow()
{

}

MeGlWindow::MeGlWindow(QApplication* app, ImgnViewport* ocGame)
{
	this->app = app;
	this->viewport = ocGame;
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
