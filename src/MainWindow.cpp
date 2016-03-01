#include "MainWindow.h"
#include "Logger.h"
#include "PlaybackControlButton.h"
#include "PlaylistModel.h"
#include "PlaylistView.h"
#include "Slider.h"
#include "PlaylistViewDelegate.h"
#include "Utils.h"
#include "VolumeWidget.h"

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
	resize(640, 480); // TODO Should be depends on screen resolution.
	setWindowTitle("SPlay");

	mPlayModel = new PlaylistModel{};
	mPlayer.setPlaylist(mPlayModel->PlaylistPtr());

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

void MainWindow::OnSeekForward()
{
	qDebug() << "MainWindow::OnSeekForward";
	mPosSldr->triggerAction(QSlider::SliderPageStepAdd);
}

void MainWindow::OnSeekBackward()
{
	qDebug() << "MainWindow::OnSeekBackward";
	mPosSldr->triggerAction(QSlider::SliderPageStepSub);
}

void MainWindow::OnTogglePlayback()
{
	if (mPlayer.mediaStatus() == QMediaPlayer::NoMedia) {
		return;
	} else if (mPlayer.state() == QMediaPlayer::PlayingState) {
		mPlayer.pause();
		mPlayBtn->setIcon(QIcon{ ":/btn_play" });
	} else {
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
	connect(mOpenFileAct, &QAction::triggered, this, &MainWindow::_OnOpenFiles);

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
	QWidget* cw{ new QWidget{ this } };
	setCentralWidget(cw);

	QBoxLayout* mainLayout{ new QVBoxLayout };

	QBoxLayout* controlLayout{ new QHBoxLayout };

	QHBoxLayout* controlLeftLayout{ new QHBoxLayout };
	QLabel* tmp{ new QLabel{ this } }; // TODO Invisible label.
	controlLeftLayout->addWidget(tmp);
	controlLeftLayout->addStretch();

	controlLayout->addLayout(controlLeftLayout);

	QHBoxLayout* controlCenterLayout{ new QHBoxLayout };
	mPrevBtn = new PlaybackControlButton{ this, QSize{ 36, 36 },
		QIcon{ ":/btn_previous" }, QSize{ 24, 24 }, tr("Previous") };
	connect(mPrevBtn, &QPushButton::clicked,
		mPlayModel, &PlaylistModel::OnPrevious);
	controlCenterLayout->addWidget(mPrevBtn);
	controlCenterLayout->addSpacing(15);

	mPlayBtn = new PlaybackControlButton{ this, QSize{ 50, 50 },
		QIcon{ ":/btn_play" }, QSize{ 40, 40 }, tr("Play") };
	connect(mPlayBtn, &QPushButton::clicked,
		this, &MainWindow::OnTogglePlayback);
	controlCenterLayout->addWidget(mPlayBtn);
	controlCenterLayout->addSpacing(15);

	mNextBtn = new PlaybackControlButton{ this, QSize{ 36, 36 },
		QIcon{ ":/btn_next" }, QSize{ 24, 24 }, tr("Next") };
	connect(mNextBtn, &QPushButton::clicked,
		mPlayModel, &PlaylistModel::OnNext);
	controlCenterLayout->addWidget(mNextBtn);

	controlLayout->addLayout(controlCenterLayout);

	QHBoxLayout* controlRightLayout{ new QHBoxLayout };
	controlRightLayout->addStretch();
	mVolBtn = new VolumeWidget(this);
	mVolBtn->setMinimumWidth(150);
	mVolBtn->setToolTip(tr("Adjust volume"));
	mVolBtn->SetVolume(mPlayer.volume());
	connect(mVolBtn, &VolumeWidget::VolumeChanged,
		&mPlayer, &QMediaPlayer::setVolume);
	controlRightLayout->addWidget(mVolBtn);

	controlLayout->addLayout(controlRightLayout);
	mainLayout->addLayout(controlLayout);

	QHBoxLayout* timeLayout{ new QHBoxLayout };
	timeLayout->setMargin(0);
	timeLayout->addStretch();
	mTimeLbl = new QLabel{ tr("00:00"), this };
	mTimeLbl->setAlignment(Qt::AlignCenter);
	mTimeLbl->setToolTip(tr("Playback time"));
	timeLayout->addWidget(mTimeLbl);
	timeLayout->addSpacing(15);

	mainLayout->addLayout(timeLayout);

	mPosSldr = new Slider{ Qt::Horizontal, this };
	connect(mPosSldr, &QSlider::valueChanged, this, &MainWindow::_OnSetPosition);
	mainLayout->addWidget(mPosSldr);

	mPlayView = new PlaylistView{ this };
	PlaylistViewDelegate* delegate = new PlaylistViewDelegate{ mPlayView };
	connect(mPlayModel, &PlaylistModel::NewIndex,
		delegate, &PlaylistViewDelegate::SetNewIndex);
	mPlayView->setItemDelegate(delegate);
	mPlayView->setModel(mPlayModel);
	connect(mPlayView, &PlaylistView::MediaIndexChanged,
		mPlayModel, &PlaylistModel::OnMediaIndexChanged);
	connect(mPlayView, &PlaylistView::Insert,
		mPlayModel, &PlaylistModel::OnInsert);
	connect(mPlayView, &PlaylistView::Move,
		mPlayModel,	&PlaylistModel::OnMove);
	connect(mPlayView, &PlaylistView::Remove,
		mPlayModel, &PlaylistModel::OnRemove);
	mainLayout->addWidget(mPlayView);

	centralWidget()->setLayout(mainLayout);
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
	qDebug() << "MainWindow::_OnHandleError";
	const auto errStr = mPlayer.errorString();
	SPLAY_LOG_CRITICAL(errStr.toStdString().c_str());
	QMessageBox::critical(this, tr("SPlay error"), errStr);
}

void MainWindow::_OnOpenFiles()
{
	const QStringList audioPaths = QStandardPaths::standardLocations(
		QStandardPaths::MusicLocation);
	const auto dir = audioPaths.isEmpty() ?
		QDir::homePath() : audioPaths.first();

	const auto urls = QFileDialog::getOpenFileUrls(this, tr("Open files"),
		QUrl::fromLocalFile(dir), tr("MP3 files (*.mp3);;All files (*.*)"));

	if (!urls.isEmpty()) {
		mPlayModel->Open(urls);
		OnTogglePlayback();
	}
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

void MainWindow::_OnUpdatePosition(qint64 val)
{
	mPosSldr->setValue(val);
	mTimeLbl->setText(utils::MillisecondsToHhMmSs(val));
}

} // namespace splay
