#include "Application.h"

namespace splay
{

Application::Application(int& argc, char** argv)
	: QApplication(argc, argv)
{
	setOrganizationName("SM");
	setApplicationName("SPlay");

	// Load translations.
	// Parse command line arguments.
	// Show main window.
}

Application::~Application()
{
	//delete mMainWnd;
}

} // namespace splay
