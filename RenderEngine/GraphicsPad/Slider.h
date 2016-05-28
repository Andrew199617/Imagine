#pragma once
#pragma warning(push)
#pragma warning (disable:4127)
#include <QtGui\qwidget>
class QSlider;
class QLabel;

class DebugSlider : public QWidget
{
	Q_OBJECT

		QSlider* slider;
	QLabel* label;
	float sliderGranularity;
	float min;
	float max;
	private slots:
	void sliderValueChanged();
signals:
	void valueChanged(float newValue);

public:

	std::string name;
	DebugSlider(std::string name = "",
		float min = -10.0f, float max = 10.0f,
		bool textOnLeft = false, float granularity = 40.0);
	float value() const;
	void setValue(float newValue);
};

#pragma warning(pop)

