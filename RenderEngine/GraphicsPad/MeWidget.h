#pragma once
#pragma warning(push)
#pragma warning (disable:4251)
#pragma warning (disable:4127)
#include <QtGui\qvboxlayout>
#include <QtGui\QLineEdit>
#include "DetailsLayout.h"
#include "Hierarchy.h"
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

	QGridLayout* mainLayout;
	QHBoxLayout* meGlWindowLayout;

	QHBoxLayout* toolsLayout;
	QPushButton* playButton;
	QIcon* playIcon;
	QIcon* pauseIcon;

	QLabel* ObjectName;
	DetailsLayout* detailsLayout;
	Hierarchy* hierarchyLayout;

	QMenu* fileMenu;
	QAction* openAct;

	QMenu* gameObjectMenu;
	QAction* addObjectAct;
	QAction* addCubeAct;
	QAction* addSphereAct;
	QAction* addPlaneAct;

	QMenu* windowMenu;
	QAction* showDetails;
	QAction* showTools;
	QAction* showHierarchy;

	OpenFileDialog openFileDialog;
	MeGlWindow* meGlWindow;
	MeModel* theModel;
public:
	MeWidget(MeGlWindow* meGl, MeModel*);

private:
	void CreateActions();
	void CreateMenus();
	void AddTools();
	void AddGlWindow();
	void AddObjectDetails();
	void AddHierarchy();
	
protected:
	void mousePressEvent(QMouseEvent*);

private slots:
	void WindowsShowEvent();
	void openingFile();
	void AddObject();
	void AddCube();
	void AddSphere();
	void AddPlane();
	void OnPlayButtonPress();
};

#pragma warning(pop)



