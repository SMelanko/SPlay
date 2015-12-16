#pragma once

#ifndef _SPLAY_MAIN_WINDOW_H_
#define _SPLAY_MAIN_WINDOW_H_

#include <QMainWindow>

QT_FORWARD_DECLARE_CLASS(QAbstractButton)
QT_FORWARD_DECLARE_CLASS(QSlider)

namespace splay
{

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	//! Constructor.
	explicit MainWindow(QWidget* parent = Q_NULLPTR);
	//! Destructor.
	~MainWindow();

private:
	//! Play/pause button.
	QAbstractButton* mPlayBtn;
	//! Skip backward button.
	QAbstractButton* mBackwardBtn;
	//! Skip forward button.
	QAbstractButton* mForwardBtn;
	//! Seek slider.
	QSlider* mPosSldr;
};

} // namespace splay

#endif // _SPLAY_MAIN_WINDOW_H_
