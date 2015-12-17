#pragma once

#ifndef _SPLAY_MAIN_WINDOW_H_
#define _SPLAY_MAIN_WINDOW_H_

#include <QMainWindow>

QT_FORWARD_DECLARE_CLASS(QAbstractButton)
QT_FORWARD_DECLARE_CLASS(QAction)
QT_FORWARD_DECLARE_CLASS(QMenu)
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
	//! Creates application actions.
	void _CreateActions();
	//! Creates application menu.
	void _CreateMenu();

private:
	//! Play/pause button.
	QAbstractButton* mPlayBtn;
	//! Skip backward button.
	QAbstractButton* mBackwardBtn;
	//! Skip forward button.
	QAbstractButton* mForwardBtn;
	//! Seek slider.
	QSlider* mPosSldr;

	//
	// Actions.
	//

	//! Exit the application.
	QAction* mExitAct;

	//
	// Menu.
	//

	//! File.
	QMenu* mFileMenu;
};

} // namespace splay

#endif // _SPLAY_MAIN_WINDOW_H_
