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
class ContentBrowser;

class ImgnMainWindow : public QMainWindow
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

	ContentBrowser* contentBrowser;

	Hierarchy* hierarchyLayout;

	QMenu* fileMenu;
	QAction* openAct;
	QAction* saveAct;

	QMenu* editMenu;
	QAction* duplicateObjectAct;
	QAction* deleteObjectAct;

	QMenu* gameObjectMenu;
	QAction* addObjectAct;
	QAction* addCubeAct;
	QAction* addSphereAct;
	QAction* addPlaneAct;

	QMenu* windowMenu;
	QAction* showDetails;
	QAction* showTools;
	QAction* showHierarchy;
	QAction* showContentBrowser;

	OpenFileDialog openFileDialog;
	MeGlWindow* meGlWindow;
public:
	ImgnMainWindow(MeGlWindow* meGl);
private:
	void CreateActions();
	void CreateMenus();
	void AddTools();
	void AddGlWindow();
	void AddObjectDetails();
	void AddHierarchy();
	void AddContentBrowser();
	
protected:
	void mousePressEvent(QMouseEvent*) override;
	void leaveEvent(QEvent*) override;
	void closeEvent(QCloseEvent *) override;

private slots:
	void WindowsShowEvent();
	void openingFile();
	void DuplicateObject();
	void DeleteObject();
	void AddObject();
	void AddCube();
	void AddSphere();
	void AddPlane();
	void OnPlayButtonPress();
	void Save();
};




