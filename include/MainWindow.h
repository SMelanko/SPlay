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

class PlaylistModel;
class PlaylistView;
class VolumeButton;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	//! Constructor.
	explicit MainWindow(QWidget* parent = Q_NULLPTR);
	//! Destructor.
	~MainWindow();

public slots:
	//! Plays a chosen track.
	void OnPlayFile(const QString& filePath);
	//! Plays/pauses a track from the playlist.
	void OnTogglePlayback();

private:
	//! Creates application actions.
	void _CreateActions();
	//! Creates central widget.
	void _CreateCentralWgt();
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
	//! Volume button.
	VolumeButton* mVolBtn;

	//
	// Actions.
	//

	//! File
	QAction* mOpenFileAct;
	QAction* mExitAct;
	//! Settings.
	QAction* mPreferecesAct;
	//! Help
	QAction* mAboutAct;
	QAction* mAboutQtAct;

	//
	// Menu.
	//

	QMenu* mFileMenu;
	QMenu* mSettingsMenu;
	QMenu* mHelpMenu;

	//! Playlist table model.
	PlaylistModel* mPlayModel;
	//! Playlist table view.
	PlaylistView* mPlayView;

	bool state;
};

} // namespace splay

#endif // _SPLAY_MAIN_WINDOW_H_
