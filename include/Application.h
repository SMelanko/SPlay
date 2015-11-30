#pragma once

#ifndef _SPLAY_APPLICATION_H_
#define _SPLAY_APPLICATION_H_

#include <QCoreApplication>

namespace splay
{

class Application : public QCoreApplication
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
