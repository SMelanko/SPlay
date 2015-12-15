#include "Application.h"
#include "MainWindow.h"

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

} // namespace splay
