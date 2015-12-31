#include "Application.h"
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
	//setWindowIcon(QIcon(":/logo.png"));

	mMainWnd = new MainWindow{};
	mMainWnd->show();

	// Load translations.
	// Parse command line arguments.
	// Show main window.
}

Application::~Application()
{
	delete mMainWnd;
}

bool Application::notify(QObject* receiver, QEvent* event)
{
	bool done = true;

	try {
		done = QApplication::notify(receiver, event);
	} catch (const std::exception e) {
		qDebug() << e.what();
	} catch (...) {
		qDebug() << "SPlay unhandled exception.";
	}

	return done;
}

} // namespace splay
