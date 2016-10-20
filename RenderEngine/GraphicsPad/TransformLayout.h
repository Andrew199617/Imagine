#pragma once
#include "ImgnComponent.h"
class QLabel;
class QHBoxLayout;
class QLineEdit;
#include <string>
#define numXYZ 9

using std::string;

class TransformLayout :
	public ImgnComponent
{
	Q_OBJECT

	QHBoxLayout* positionLayout;
	QHBoxLayout* scaleLayout;
	QHBoxLayout* rotateLayout;

	QLabel* positionLabel;
	QLabel* scaleLabel;
	QLabel* rotateLabel;

	QLabel* XYZ_Labels[numXYZ];
	QLineEdit* XYZ_TextBoxs[numXYZ];
	float values[numXYZ];
public:
	TransformLayout();
	~TransformLayout();
	bool Initialize();
	void CreateWidgets();
	void SetupLabels(string name, QHBoxLayout** layout, QLabel** nameLabel, int x, int y, int z);
	void SetTextBoxValues();
	void ClearFocus();
	void SetHidden(bool);
	void SetMaximumSize(int Width, int Height);
	void DeleteWidgets();

private slots:
	void XYZChanged();
};

