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
	QVBoxLayout* objectDetailsLayout;
	QCheckBox* discardBasedOnDepth;
	QCheckBox* useRegularDepth;
	QCheckBox* checkboxNormals;

	QLineEdit* ObjName;
	QPushButton* getFileLocation;
	QLineEdit* getFileLocationLabel;
	QPushButton* getTextureLocation;
	QPushButton* submit;

	DebugSlider* lightY;
	DebugSlider* uD;
	DebugSlider* uR;

	QMenu *fileMenu;
	QMenu *gameObjectMenu;
	QAction *openAct;
	QAction* addObjectAct;

	OpenFileDialog openFileDialog;
	MeGlWindow* meGlWindow;
	MeModel* theModel;
public:
	MeWidget(MeGlWindow* meGl, MeModel*);
	private slots:
	void sliderValueChanged();
	void openingFile();
	void openingTexture();
	void checkBoxChanged();

private:
	void createActions();
	void createMenus();

};

#pragma warning(pop)



