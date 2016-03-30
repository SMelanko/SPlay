#include "VolumeWidget.h"

#include <QHBoxLayout>
#include <QSlider>

namespace splay
{

VolumeWidget::VolumeWidget(QWidget* parent)
	: QWidget{ parent }
	, mSlider{ Q_NULLPTR }
{
	QBoxLayout* layout{ new QHBoxLayout{ this } };

	mSlider = new QSlider{ Qt::Horizontal, this };
	mSlider->setFixedHeight(20);
	mSlider->setRange(0, 100);

	connect(mSlider, &QAbstractSlider::valueChanged,
		this, &VolumeWidget::VolumeChanged);

	layout->addWidget(mSlider);

	setLayout(layout);
}

void VolumeWidget::DecreaseVolume()
{
	mSlider->triggerAction(QSlider::SliderPageStepSub);
}

void VolumeWidget::IncreaseVolume()
{
	mSlider->triggerAction(QSlider::SliderPageStepAdd);
}

void VolumeWidget::SetVolume(int volume)
{
	mSlider->setValue(volume);
}

int VolumeWidget::Volume() const Q_DECL_NOEXCEPT
{
	return mSlider->value();
}

} // namespace splay
