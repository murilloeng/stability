//std
#include <cstdlib>

//qt
#include <QtWidgets/QApplication>

//stability
#include "stability/inc/Window.hpp"
#include "stability/inc/Polynomial.hpp"

int main(int argc, char** argv)
{
	// //application
	// QApplication application(argc, argv);
	// //window
	// Window window;
	// window.show();
	// //start
	// application.exec();
	Polynomial p1(1), p2(2);
	p1[0] = -1;
	p1[1] = 1;
	p2[0] = 6;
	p2[1] = -5;
	p2[2] = 1;
	p1.print();
	p2.print();
	Polynomial p3 = p1 * p2;
	Polynomial p4 = p2 * p1;
	p3.print();
	p4.print();
	Polynomial p5 = p3 / p1;
	Polynomial p6 = p3 / p2;
	p5.print();
	p6.print();
	//return
	return EXIT_SUCCESS;
}