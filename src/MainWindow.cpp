#include "MainWindow.h"
#include "Logger.h"
#include "PlaylistModel.h"
#include "PlaylistView.h"
#include "Slider.h"
#include "VolumeButton.h"

#include <QAction>
#include <QApplication>
#include <QBoxLayout>
#include <QFileDialog>
#include <QLabel>
#include <QMenuBar>
#include <QMessageBox>
#include <QPushButton>
#include <QSlider>
#include <QStandardPaths>
#include <QStatusBar>
#include <QStyle>
#include <QTime>

namespace splay
{

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow { parent }
{
	resize(640, 480);
	setWindowTitle("SPlay");

	_CreateActions();
	_CreateMenu();
	_CreateCentralWgt();

	typedef void(QMediaPlayer::*ErrorSignal)(QMediaPlayer::Error);
	connect(&mPlayer, static_cast<ErrorSignal>(&QMediaPlayer::error),
		this, &MainWindow::_OnHandleError);
	connect(&mPlayer, &QMediaPlayer::durationChanged,
		this, &MainWindow::_OnUpdateDuration);
	connect(&mPlayer, &QMediaPlayer::positionChanged,
		this, &MainWindow::_OnUpdatePosition);

	statusBar()->showMessage(tr("SPlay music player"));
}

MainWindow::~MainWindow()
{
	mPlayer.stop();

	delete mPlayModel;
}

void MainWindow::OnPlayFile(const QString& filePath)
{
	mPlayBtn->setIcon(QIcon{ ":/btn_pause" });
	mPlayer.setMedia(QUrl::fromLocalFile(filePath));
	mPlayer.play();
}

void MainWindow::OnSeekForward()
{
	qDebug() << "triggerAction(QSlider::SliderPageStepAdd);";
	mPosSldr->triggerAction(QSlider::SliderPageStepAdd);
}

void MainWindow::OnSeekBackward()
{
	qDebug() << "triggerAction(QSlider::SliderPageStepSub);";
	mPosSldr->triggerAction(QSlider::SliderPageStepSub);
}

void MainWindow::OnTogglePlayback()
{
	if (mPlayer.mediaStatus() == QMediaPlayer::NoMedia) {
		return;
	}
	else if (mPlayer.state() == QMediaPlayer::PlayingState) {
		mPlayer.pause();
		mPlayBtn->setIcon(QIcon{ ":/btn_play" });
	}
	else {
		mPlayer.play();
		mPlayBtn->setIcon(QIcon{ ":/btn_pause" });
	}
}

void MainWindow::_CreateActions()
{
	mOpenFileAct = new QAction{ tr("&Open"), this };
	mOpenFileAct->setShortcut(QKeySequence::Open);
	mOpenFileAct->setStatusTip(
		tr("Replace current playlist with chosen file(s), then start playing."));
	connect(mOpenFileAct, &QAction::triggered, this, [&]() {
		const QStringList musicPaths = QStandardPaths::standardLocations(
			QStandardPaths::MusicLocation);
		const auto dir = musicPaths.isEmpty() ? QDir::homePath() : musicPaths.first();

		const QString filePath = QFileDialog::getOpenFileName(
			this, tr("Open file"), dir, tr("MP3 files (*.mp3);;All files (*.*)"));

		if (!filePath.isEmpty()) {
			OnPlayFile(filePath);
		}
	});

	mExitAct = new QAction{ tr("E&xit"), this };
	mExitAct->setShortcut(QKeySequence::Quit);
	mExitAct->setStatusTip(tr("Exit SPlay."));
	connect(mExitAct, &QAction::triggered, this, &MainWindow::close); // QApp::quit ?

	mPreferecesAct = new QAction{ tr("&Preferences"), this };
	//mPrefereces->setShortcut
	mPreferecesAct->setStatusTip(tr("SPlay settings."));

	mAboutAct = new QAction{ tr("&About"), this };
	//mPrefereces->setShortcut
	mAboutAct->setStatusTip(tr("Show the SPlay's About box"));

	mAboutQtAct = new QAction{ tr("About &Qt"), this };
	mAboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
	connect(mAboutQtAct, &QAction::triggered, qApp, &QApplication::aboutQt);
}

void MainWindow::_CreateCentralWgt()
{
	QWidget* cw{ new QWidget };
	setCentralWidget(cw);

	QBoxLayout* ml{ new QVBoxLayout };

	QBoxLayout* al{ new QHBoxLayout };

	mVolBtn = new VolumeButton(this);
	mVolBtn->setToolTip(tr("Adjust volume"));
	mVolBtn->SetVolume(mPlayer.volume());
	connect(mVolBtn, &VolumeButton::VolumeChanged,
		&mPlayer, &QMediaPlayer::setVolume);
	al->addWidget(mVolBtn);

	al->addStretch(1);
	mBackwardBtn = new QPushButton{ this };
	mBackwardBtn->setEnabled(true);
	mBackwardBtn->setFixedSize(36, 36);
	mBackwardBtn->setIcon(QIcon{ ":/btn_rewind" });
	mBackwardBtn->setIconSize(QSize{ 28, 28 });
	mBackwardBtn->setToolTip(tr("Previous"));
	al->addWidget(mBackwardBtn);
	al->addSpacing(15);

	mPlayBtn = new QPushButton{ this };
	mPlayBtn->setEnabled(true);
	mPlayBtn->setFixedSize(50, 50);
	mPlayBtn->setIcon(QIcon{ ":/btn_play" });
	mPlayBtn->setIconSize(QSize{ 40, 40 });
	mPlayBtn->setToolTip(tr("Play"));
	connect(mPlayBtn, &QPushButton::clicked, this, &MainWindow::OnTogglePlayback);
	al->addWidget(mPlayBtn);
	al->addSpacing(15);

	mForwardBtn = new QPushButton{ this };
	mForwardBtn->setEnabled(true);
	mForwardBtn->setFixedSize(36, 36);
	mForwardBtn->setIcon(QIcon{ ":/btn_forward" });
	mForwardBtn->setIconSize(QSize{ 28, 28 });
	mForwardBtn->setToolTip(tr("Next"));
	al->addWidget(mForwardBtn);
	al->addStretch(1);

	mTimeLbl = new QLabel{ tr("00:00"), this };
	mTimeLbl->setAlignment(Qt::AlignCenter);
	mTimeLbl->setFixedSize(68, 36);
	mTimeLbl->setStyleSheet("border: 1px solid #357EC7; border-radius: 3px;");
	al->addWidget(mTimeLbl);

	ml->addLayout(al);

	mPosSldr = new Slider{ Qt::Horizontal, this };
	connect(mPosSldr, &QSlider::valueChanged, this, &MainWindow::_OnSetPosition);
	ml->addWidget(mPosSldr);

	mPlayModel = new PlaylistModel{};
	mPlayView = new PlaylistView{ this };
	mPlayView->setModel(mPlayModel);
	connect(mPlayView, &PlaylistView::Insert, mPlayModel, &PlaylistModel::OnInsert);
	connect(mPlayView, &PlaylistView::Move, mPlayModel, &PlaylistModel::OnMove);
	connect(mPlayView, &PlaylistView::Remove, mPlayModel, &PlaylistModel::OnRemove);
	ml->addWidget(mPlayView);

	centralWidget()->setLayout(ml);
}

void MainWindow::_CreateMenu()
{
	mFileMenu = menuBar()->addMenu(tr("&File"));
	mFileMenu->addAction(mOpenFileAct);
	mFileMenu->addSeparator();
	mFileMenu->addAction(mExitAct);

	mSettingsMenu = menuBar()->addMenu(tr("&Settings"));
	mSettingsMenu->addAction(mPreferecesAct);

	mHelpMenu = menuBar()->addMenu(tr("&Help"));
	mHelpMenu->addAction(mAboutAct);
	mHelpMenu->addAction(mAboutQtAct);
}

void MainWindow::_OnHandleError() Q_DECL_NOEXCEPT
{
	const auto errStr{ mPlayer.errorString() };
	SPLAY_LOG_CRITICAL(errStr.toStdString().c_str());
	QMessageBox::critical(this, tr("SPlay error"), errStr);
}

void MainWindow::_OnSetPosition(int position)
{
	// Avoid seeking when the slider value change is triggered from _OnUpdatePosition.
	if (qAbs(mPlayer.position() - position) > 99) {
		mPlayer.setPosition(position);
	}
}

void MainWindow::_OnUpdateDuration(qint64 duration)
{
	mPosSldr->setRange(0, duration);
	mPosSldr->setPageStep(duration / 10);
}

void MainWindow::_OnUpdatePosition(qint64 pos)
{
	mPosSldr->setValue(pos);

	Q_DECL_CONSTEXPR int coef = 60000;
	int minutes = static_cast<int>(pos / coef);
	int seconds = qRound((pos % coef) / 1000.0);

	if (seconds == 60) {
		++minutes;
		seconds = 0;
	}

	QTime time{ 0, minutes, seconds };
	mTimeLbl->setText(time.toString(tr("mm:ss")));
}

} // namespace splay
