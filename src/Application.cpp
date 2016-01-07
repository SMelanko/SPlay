#include "Application.h"
#include "Logger.h"
#include "MainWindow.h"

#include <QDebug>

namespace splay
{

Application::Application(int& argc, char** argv)
	: QApplication{ argc, argv }
{
	setApplicationName("SPlay");
	setOrganizationName("SM"); // Fictitious parameter.
	setOrganizationDomain("sm.com.ua"); // Fictitious parameter.
	setApplicationDisplayName(tr("SPlay music player"));
	setWindowIcon(QIcon(":/btn_play"));

	mMainWnd = new MainWindow{};
	mMainWnd->show();

	// Load translations.
	// Parse command line arguments.
}

Application::~Application()
{
	delete mMainWnd;
}

bool Application::notify(QObject* receiver, QEvent* event)
{
	QString msg;

	try {
		return QApplication::notify(receiver, event);
	} catch (const std::exception& e) {
		msg = _ErrMsg(e.what(), receiver, event);
	} catch (...) {
		msg = _ErrMsg("<Unknown>", receiver, event);
	}

	qFatal(msg.toStdString().c_str());
	SPLAY_LOG_ERROR(msg.toStdString().c_str());

	return false;
}

QString Application::_ErrMsg(const char* msg,
	const QObject* receiver, const QEvent* event) const
{
	return QString{ "Error: %1. Sending event %2 to object %3 (%4)" }
		.arg(msg)
		.arg(typeid(*event).name())
		.arg(qPrintable(receiver->objectName()))
		.arg(typeid(*receiver).name());
}

} // namespace splay
