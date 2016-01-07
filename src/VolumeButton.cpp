#include "VolumeButton.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QMenu>
#include <QSlider>
#include <QWidgetAction>

namespace splay
{

VolumeButton::VolumeButton(QWidget* parent)
	: QToolButton(parent)
	, mLabel(Q_NULLPTR)
	, mMenu(Q_NULLPTR)
	, mSlider(Q_NULLPTR)
{
	setFixedSize(36, 36);
	setIcon(QIcon{ ":/btn_volume" });
	setIconSize(QSize{ 28, 28 });
	setPopupMode(QToolButton::InstantPopup);

	QWidget* popup = new QWidget(this);

	mSlider = new QSlider(Qt::Horizontal, popup);
	mSlider->setRange(0, 100);
	connect(mSlider, &QAbstractSlider::valueChanged,
		this, &VolumeButton::VolumeChanged);

	mLabel = new QLabel(popup);
	mLabel->setAlignment(Qt::AlignCenter);
	mLabel->setNum(100);
	mLabel->setMinimumWidth(mLabel->sizeHint().width());

	typedef void(QLabel::*IntSlot)(int);
	connect(mSlider, &QAbstractSlider::valueChanged,
		mLabel, static_cast<IntSlot>(&QLabel::setNum));

	QBoxLayout* popupLayout = new QHBoxLayout(popup);
	popupLayout->setMargin(5);
	popupLayout->addWidget(mSlider);
	popupLayout->addWidget(mLabel);

	QWidgetAction* action = new QWidgetAction(this);
	action->setDefaultWidget(popup);

	mMenu = new QMenu(this);
	mMenu->addAction(action);
	setMenu(mMenu);
}

void VolumeButton::DecreaseVolume()
{
	mSlider->triggerAction(QSlider::SliderPageStepSub);
}

void VolumeButton::IncreaseVolume()
{
	mSlider->triggerAction(QSlider::SliderPageStepAdd);
}

void VolumeButton::SetVolume(int volume)
{
	mSlider->setValue(volume);
}

int VolumeButton::Volume() const Q_DECL_NOEXCEPT
{
	return mSlider->value();
}

} // namespace splay
