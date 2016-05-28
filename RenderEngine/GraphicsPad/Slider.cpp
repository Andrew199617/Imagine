#include "Slider.h"
#pragma warning(push)
#pragma warning (disable:4127)
#pragma warning (disable:4244)
#pragma warning (disable:4251)
#include <QtGui\qvboxlayout>
#include <QtGui\qslider>
#include <QtGui\qlabel>

DebugSlider::DebugSlider(std::string name, float min, float max, bool textOnLeft, float granularity)
{

	QLayout* layout;
	this->min = min;
	this->max = max;
	sliderGranularity = granularity;
	setLayout(layout = textOnLeft ? (QLayout*)new QHBoxLayout : new QVBoxLayout);
	this->name = name;
	layout->addWidget(label = new QLabel(name.c_str()));
	label->setMinimumWidth(35);
	layout->addWidget(slider = new QSlider);
	label->setAlignment(Qt::AlignCenter);
	slider->setOrientation(Qt::Horizontal);
	slider->setMinimum(0);
	slider->setMaximum(sliderGranularity);
	slider->activateWindow();
	connect(slider, SIGNAL(valueChanged(int)),
		this, SLOT(sliderValueChanged()));
	sliderValueChanged();

}
float DebugSlider::value() const
{
	return min + (max - min) * (slider->value() / sliderGranularity);
}
void DebugSlider::setValue(float newValue)
{
	float spot = (newValue - min) / (max - min);
	slider->setValue(spot * sliderGranularity);
}
void DebugSlider::sliderValueChanged()
{
	label->setText(name.c_str() + QString::number(value()));
	emit valueChanged(value());
}


#pragma warning(pop)

