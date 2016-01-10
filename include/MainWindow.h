#pragma once

#ifndef _SPLAY_MAIN_WINDOW_H_
#define _SPLAY_MAIN_WINDOW_H_

#include <QMainWindow>
#include <QMediaPlayer>

QT_FORWARD_DECLARE_CLASS(QAbstractButton)
QT_FORWARD_DECLARE_CLASS(QAction)
QT_FORWARD_DECLARE_CLASS(QLabel)
QT_FORWARD_DECLARE_CLASS(QMenu)

namespace splay
{

class PlaylistModel;
class PlaylistView;
class Slider;
class VolumeButton;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	//! Constructor.
	explicit MainWindow(QWidget* parent = Q_NULLPTR);
	//! Destructor.
	virtual ~MainWindow();

	//! Disable copy constructor and copy assign operator.
	Q_DISABLE_COPY(MainWindow)

public Q_SLOTS:
	//! Plays a chosen track.
	void OnPlayFile(const QString& filePath);
	//! Triggers a slider action.
	void OnSeekForward();
	//! Triggers a slider action.
	void OnSeekBackward();
	//! Plays/pauses a track from the playlist.
	void OnTogglePlayback();

private:
	//! Creates application actions.
	void _CreateActions();
	//! Creates central widget.
	void _CreateCentralWgt();
	//! Creates application menu.
	void _CreateMenu();

private Q_SLOTS:
	//! Shows a string describling the last error condition.
	void _OnHandleError() Q_DECL_NOEXCEPT;
	//! Sets the playback position by the slider.
	void _OnSetPosition(int position);
	//! Updates the slider duration according with current audio.
	void _OnUpdateDuration(qint64 duration);
	//! Updates the playback position of the current audio.
	void _OnUpdatePosition(qint64 pos);

private:
	//! Play/pause button.
	QAbstractButton* mPlayBtn;
	//! Skip backward button.
	QAbstractButton* mBackwardBtn;
	//! Skip forward button.
	QAbstractButton* mForwardBtn;
	//! Seek slider.
	Slider* mPosSldr;
	//! Volume button.
	VolumeButton* mVolBtn;
	//! Playlist table model.
	PlaylistModel* mPlayModel;
	//! Playlist table view.
	PlaylistView* mPlayView;
	//! Class allows the playing of a media source.
	QMediaPlayer mPlayer;
	//! Shows current audio time.
	QLabel* mTimeLbl;

	//
	// Menu.
	//

	QMenu* mFileMenu;
	QMenu* mSettingsMenu;
	QMenu* mHelpMenu;

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
};

} // namespace splay

#endif // _SPLAY_MAIN_WINDOW_H_
