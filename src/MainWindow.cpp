#include "MainWindow.h"

#include <QBoxLayout>
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

	// Create and set central widget.
	QWidget* cw{ new QWidget };
	setCentralWidget(cw);

	QBoxLayout* ml{ new QVBoxLayout };

	QBoxLayout* al{ new QHBoxLayout };

	al->addStretch(1);
	mBackwardBtn = new QPushButton{ this };
	mBackwardBtn->setEnabled(true);
	mBackwardBtn->setFixedSize(30, 30);
	mBackwardBtn->setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward));
	mBackwardBtn->setToolTip(tr("Previous"));
	al->addWidget(mBackwardBtn);
	al->addSpacing(20);

	mPlayBtn = new QPushButton{ this };
	mPlayBtn->setEnabled(true); // false
	mPlayBtn->setFixedSize(60, 60);
	mPlayBtn->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
	mPlayBtn->setToolTip(tr("Play"));
	al->addWidget(mPlayBtn);
	al->addSpacing(20);

	mForwardBtn = new QPushButton{ this };
	mForwardBtn->setEnabled(true); // false
	mForwardBtn->setFixedSize(30, 30);
	mForwardBtn->setIcon(style()->standardIcon(QStyle::SP_MediaSkipForward));
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

} // namespace splay
