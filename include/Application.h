#pragma once

#ifndef _SPLAY_APPLICATION_H_
#define _SPLAY_APPLICATION_H_

#include <QApplication>

namespace splay
{

class MainWindow;

class Application : public QApplication
{
	Q_OBJECT

public:
	//! Constructor.
	explicit Application(int& argc, char** argv);
	//! Destructor.
	virtual ~Application();

	//! Disable copy constructor and copy assign operator.
	Q_DISABLE_COPY(Application)

protected:
	//! Returns the value that is returned from the receiver's event handler.
	bool notify(QObject* receiver, QEvent* event) Q_DECL_OVERRIDE;

private:
	//! Makes a message error according the exception specification.
	QString _ErrMsg(const char* msg,
		const QObject* receiver, const QEvent* event) const;

private:
	//! Main window handle.
	MainWindow* mMainWnd;
};

} // namespace splay

#endif // _SPLAY_APPLICATION_H_
