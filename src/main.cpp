//std
#include <cstdlib>

//qt
#include <QtWidgets/QApplication>

//stability
#include "stability/inc/Window.hpp"

int main(int argc, char** argv)
{
	//application
	QApplication application(argc, argv);
	//window
	Window window;
	window.show();
	//start
	application.exec();
	//return
	return EXIT_SUCCESS;
}