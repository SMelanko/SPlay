#include "MainWindow.h"

namespace splay
{

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
{
	resize(640, 480);
	setWindowTitle("SPlay");
}

MainWindow::~MainWindow()
{
}

} // namespace splay
