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

class MeGlWindow;
class QApplication;

class MeWidget : public QWidget
{
	Q_OBJECT

	QVBoxLayout* controlsLayout;
	QCheckBox* checkboxColor;
	QCheckBox* checkboxTexture;
	QCheckBox* checkboxNormals;

	QLineEdit* ObjName;
	QPushButton* getFileLocation;
	QLineEdit* getFileLocationLabel;
	QPushButton* getTextureLocation;
	QLineEdit* getTextureLocationLabel;
	QPushButton* save;

	DebugSlider* lightY;
	DebugSlider* uD;
	DebugSlider* uR;

	MeGlWindow* meGlWindow;
	MeModel* theModel;
public:
	MeWidget(MeGlWindow* meGl, MeModel*);
	private slots:
	void sliderValueChanged();
	void openingFile();
	void openingTexture();
	void checkBoxChanged();
};

#pragma warning(pop)



