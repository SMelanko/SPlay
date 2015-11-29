#pragma once

#ifndef _SPLAY_APPLICATION_H_
#define _SPLAY_APPLICATION_H_

#include <QApplication>

namespace splay
{

class Application : public QApplication
{
	Q_OBJECT

public:
	//! Constructor.
	explicit Application(int& argc, char** argv);
	//! Destructor.
	~Application();
};

} // namespace splay

#endif // _SPLAY_APPLICATION_H_
