#pragma once

#ifndef _SPLAY_MAIN_WINDOW_H_
#define _SPLAY_MAIN_WINDOW_H_

#include <QMainWindow>

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
};

} // namespace splay

#endif // _SPLAY_MAIN_WINDOW_H_
