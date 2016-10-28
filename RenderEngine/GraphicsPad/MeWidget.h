#pragma once
#include <Qt\qmainwindow.h>
#include "OpenFileDialog.h"
class SaveLogger;
class MeGlWindow;
class QApplication;
class QPushButton;
class QGridLayout;
class QHBoxLayout;
class QIcon;
class Hierarchy;
class DetailsLayout;
class ImgnToolBar;

class MeWidget : public QMainWindow
{
	Q_OBJECT

	SaveLogger* saveLogger;
	QGridLayout* mainLayout;
	QHBoxLayout* meGlWindowLayout;

	ImgnToolBar* imgnToolBar;
	QHBoxLayout* toolsLayout;
	QPushButton* playButton;
	QIcon* playIcon;
	QIcon* pauseIcon;

	Hierarchy* hierarchyLayout;

	QMenu* fileMenu;
	QAction* openAct;
	QAction* saveAct;

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
public:
	MeWidget(MeGlWindow* meGl);
private:
	void CreateActions();
	void CreateMenus();
	void AddTools();
	void AddGlWindow();
	void AddObjectDetails();
	void AddHierarchy();
	
protected:
	void mousePressEvent(QMouseEvent*) override;
	void leaveEvent(QEvent*) override;
	void closeEvent(QCloseEvent *) override;

	private slots:
	void WindowsShowEvent();
	void openingFile();
	void AddObject();
	void AddCube();
	void AddSphere();
	void AddPlane();
	void OnPlayButtonPress();
	void Save();
};




