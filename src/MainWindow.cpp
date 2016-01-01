#include "MainWindow.h"
#include "PlaylistModel.h"
#include "PlaylistView.h"
#include "VolumeButton.h"

#include <QAction>
#include <QApplication>
#include <QBoxLayout>
#include <QFileDialog>
#include <QLabel>
#include <QMenuBar>
#include <QPushButton>
#include <QSlider>
#include <QStandardPaths>
#include <QStatusBar>
#include <QStyle>

namespace splay
{

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
{
	resize(640, 480);
	setWindowTitle("SPlay");

	_CreateActions();
	_CreateMenu();
	_CreateCentralWgt();

	statusBar()->showMessage(tr("SPlay music player"));
}

MainWindow::~MainWindow()
{
	delete mPlayModel;
}

void MainWindow::OnPlayFile(const QString& filePath)
{
	state = true;
	mPlayBtn->setIcon(QIcon{ ":/btn_pause" });
	mPlayBtn->setIconSize(QSize{ 40, 40 });
}

void MainWindow::OnTogglePlayback()
{
	if (state) {
		mPlayBtn->setIcon(QIcon{ ":/btn_pause" });
		mPlayBtn->setIconSize(QSize{ 40, 40 });
		state = false;
	}
	else {
		mPlayBtn->setIcon(QIcon{ ":/btn_play" });
		mPlayBtn->setIconSize(QSize{ 40, 40 });
		state = true;
	}
}

void MainWindow::_CreateActions()
{
	mOpenFileAct = new QAction{ tr("&Open"), this };
	mOpenFileAct->setShortcut(QKeySequence::Open);
	mOpenFileAct->setStatusTip(tr("Replace current playlist with chosen file(s), then start playing."));
	connect(mOpenFileAct, &QAction::triggered, this, [&]() {
		const QStringList musicPaths = QStandardPaths::standardLocations(QStandardPaths::MusicLocation);
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
	mVolBtn->SetVolume(30);//mediaPlayer.volume());
	//connect(mVolBtn, &VolumeButton::volumeChanged, &mediaPlayer, &QMediaPlayer::setVolume);
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

	QLabel* time = new QLabel{ "3:07", this };
	time->setAlignment(Qt::AlignCenter);
	time->setFixedSize(68, 36);
	time->setStyleSheet("border: 1px solid #357EC7; border-radius: 3px;");
	al->addWidget(time);

	ml->addLayout(al);

	mPosSldr = new QSlider{ Qt::Horizontal, this };
	mPosSldr->setEnabled(true); // false
	mPosSldr->setFixedHeight(25);
	mPosSldr->setToolTip(tr("Seek"));
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

} // namespace splay
