#pragma once

#ifndef _SPLAY_VOLUME_BUTTON_H_
#define _SPLAY_VOLUME_BUTTON_H_

#include <QWidget>

QT_FORWARD_DECLARE_CLASS(QSlider)

namespace splay
{

class VolumeWidget : public QWidget
{
	Q_OBJECT

	Q_PROPERTY(int volume READ Volume WRITE SetVolume NOTIFY VolumeChanged)

public:
	//! Constructor.
	VolumeWidget(QWidget* parent = Q_NULLPTR);

public:
	//! Returns current volume value.
	int Volume() const Q_DECL_NOEXCEPT;

public Q_SLOTS:
	//! Decreases volume.
	void DecreaseVolume();
	//! Increases volume.
	void IncreaseVolume();
	//! Sets a new volume value.
	void SetVolume(int volume);

Q_SIGNALS:
	//! The signal emits volume value which has been changed.
	void VolumeChanged(int volume);

private:
	//! Slider for the volume changing.
	QSlider* mSlider;
};

} // namespace splay

#endif // _SPLAY_VOLUME_BUTTON_H_
