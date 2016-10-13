#pragma once
#pragma warning(push)
#pragma warning (disable:4251)
#pragma warning (disable:4127)
#include "QtGui\qboxlayout.h"
#include <QtGui\QLineEdit>
#include <QtGui\qkeyevent>
#pragma warning(pop)
#include <QtGui\qlabel.h>
#include <string>
#define numXYZ 9

using std::string;

class TransformLayout :
	public QVBoxLayout
{
	Q_OBJECT

	QHBoxLayout* positionLayout;
	QHBoxLayout* scaleLayout;
	QHBoxLayout* rotateLayout;

	QLabel* positionLabel;
	QLabel* scaleLabel;
	QLabel* rotateLabel;

	QLabel* XYZ_Labels[numXYZ];
	static QLineEdit* XYZ_TextBoxs[numXYZ];
	float values[numXYZ];
public:
	TransformLayout();
	~TransformLayout();
	void Initialize();
	void SetupLabels(string name, QHBoxLayout** layout, QLabel** nameLabel, int x, int y, int z);
	static void SetTextBoxValues();
	void ClearFocus();
	void SetHidden(bool);
	void SetMaximumSize(int Width, int Height);
	bool isHidden;


private slots:
	void XYZChanged();
};

