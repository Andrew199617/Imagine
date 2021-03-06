#pragma once
#pragma warning(push)
#pragma warning (disable:4127)
#include <Qt\qtimer.h>
#pragma warning(pop)
#include <Qt\qapplication.h>
#pragma warning(push)
#pragma warning (disable:4251)
#pragma warning (disable:4127)
#pragma warning (disable:4800)
#include <QtOpenGL\qglwidget>
#pragma warning(pop)
class ImgnViewport;

class MeGlWindow : public QGLWidget
{
	Q_OBJECT

	QTimer myTimer;
protected:
	void initializeGL();
	void mouseMoveEvent(QMouseEvent*);
	void mousePressEvent(QMouseEvent*);
	void resizeGL(int w, int h);
	void dragEnterEvent(QDragEnterEvent *event);
	void dropEvent(QDropEvent *event);

public:
	void Initialize();
	MeGlWindow(void);
	MeGlWindow(QApplication*, ImgnViewport*);
	void shutdown();
	bool forceShutdown();
	ImgnViewport* viewport;


	QApplication* app;
	bool ShutdownApp;

private slots:
	void myUpdate();

};


