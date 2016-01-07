#pragma once

#ifndef _SPLAY_VOLUME_BUTTON_H_
#define _SPLAY_VOLUME_BUTTON_H_

#include <QToolButton>

QT_FORWARD_DECLARE_CLASS(QLabel)
QT_FORWARD_DECLARE_CLASS(QMenu)
QT_FORWARD_DECLARE_CLASS(QSlider)

namespace splay
{

class VolumeButton : public QToolButton
{
	Q_OBJECT

	Q_PROPERTY(int volume READ Volume WRITE SetVolume NOTIFY VolumeChanged)

public:
	//! Constructor.
	VolumeButton(QWidget* parent = Q_NULLPTR);

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
	//! Button label.
	QLabel* mLabel;
	//! Menu.
	QMenu* mMenu;
	//! Widget for changing volume value.
	QSlider* mSlider;
};

} // namespace splay

#endif // _SPLAY_VOLUME_BUTTON_H_
