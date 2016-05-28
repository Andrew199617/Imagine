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
class OriginalGame;


class MeGlWindow : public QGLWidget
{
	Q_OBJECT

	QTimer myTimer;
	OriginalGame* game;
protected:
	void initializeGL();
	void mouseMoveEvent(QMouseEvent*);
public:
	MeGlWindow(void);
	MeGlWindow(QApplication*, OriginalGame*);
	void shutdown();


	QApplication* app;
	bool ShutdownApp;

	private slots:
	void myUpdate();

};


