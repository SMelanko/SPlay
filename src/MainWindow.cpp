#include "MainWindow.h"

#include <QAction>
#include <QBoxLayout>
#include <QMenuBar>
#include <QPushButton>
#include <QSlider>
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

	// Create and set central widget.
	QWidget* cw{ new QWidget };
	setCentralWidget(cw);

	QBoxLayout* ml{ new QVBoxLayout };

	QBoxLayout* al{ new QHBoxLayout };

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
	mPlayBtn->setEnabled(true); // false
	mPlayBtn->setFixedSize(50, 50);
	mPlayBtn->setIcon(QIcon{ ":/btn_play" });
	mPlayBtn->setIconSize(QSize{ 40, 40 });
	mPlayBtn->setToolTip(tr("Play"));
	al->addWidget(mPlayBtn);
	al->addSpacing(15);

	mForwardBtn = new QPushButton{ this };
	mForwardBtn->setEnabled(true); // false
	mForwardBtn->setFixedSize(36, 36);
	mForwardBtn->setIcon(QIcon{ ":/btn_forward" });
	mForwardBtn->setIconSize(QSize{ 28, 28 });
	mForwardBtn->setToolTip(tr("Next"));
	al->addWidget(mForwardBtn);
	al->addStretch(1);

	ml->addLayout(al);

	mPosSldr = new QSlider{ Qt::Horizontal, this };
	mPosSldr->setEnabled(true); // false
	mPosSldr->setFixedHeight(25);
	mPosSldr->setToolTip(tr("Seek"));
	ml->addWidget(mPosSldr);

	centralWidget()->setLayout(ml);

	statusBar()->showMessage(tr("SPlay music player"));
}

MainWindow::~MainWindow()
{
}

void MainWindow::_CreateActions()
{
	mExitAct = new QAction{ tr("E&xit"), this };
	mExitAct->setShortcut(QKeySequence::Quit);
	mExitAct->setStatusTip(tr("Exit the application"));
	connect(mExitAct, &QAction::triggered, this, &MainWindow::close);
}

void MainWindow::_CreateMenu()
{
	mFileMenu = menuBar()->addMenu(tr("&File"));
	mFileMenu->addAction(mExitAct);
}

} // namespace splay
