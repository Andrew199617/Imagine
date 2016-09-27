#pragma once
#pragma warning(push)
#pragma warning (disable:4251)
#pragma warning (disable:4127)
#include <QtGui\qvboxlayout>
#include <QtGui\QLineEdit>
#pragma warning(pop)
#include <QtGui\QPushButton>
#include <QtGui\QCheckBox>
#include <QtGui\qlabel.h>
#pragma warning(push)
#pragma warning (disable:4201)
#include <QtGui\qwidget.h>
#include "MeModel.h"
#include "Slider.h"
#include <Qt\qmainwindow.h>
#include "PostProcessingModel.h"
#include "OpenFileDialog.h"

class MeGlWindow;
class QApplication;

class MeWidget : public QMainWindow
{
	Q_OBJECT

	QVBoxLayout* controlsLayout;
	//QVBoxLayout* controlsLayout;
	QVBoxLayout* objectDetailsLayout;
	QHBoxLayout* meGlWindowLayout;
	QPushButton* ShowDetails;
	QCheckBox* discardBasedOnDepth;

	QMenu* fileMenu;
	QMenu* gameObjectMenu;
	QAction* openAct;
	QAction* addObjectAct;
	QAction* addCubeAct;
	QAction* addSphereAct;
	QAction* addPlaneAct;


	OpenFileDialog openFileDialog;
	MeGlWindow* meGlWindow;
	MeModel* theModel;
public:
	MeWidget(MeGlWindow* meGl, MeModel*);

private:
	void createActions();
	void createMenus();

private slots:
	void sliderValueChanged();
	void openingFile();
	void AddObject();
	void AddCube();
	void AddSphere();
	void AddPlane();
	void checkBoxChanged();
};

#pragma warning(pop)



