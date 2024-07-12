//std
#include <cstdlib>

//qt
#include <QtWidgets/QApplication>

//stability
#include "stability/inc/Window.hpp"
#include "stability/inc/Stability.hpp"

math::vector xs(double s, void** args)
{
	//data
	math::vector xs(2);
	const double e = *(double*) args[0];
	//path
	xs[1] = cos(M_PI * s);
	xs[0] = e * sin(M_PI * s);
	//return
	return xs;
}
math::vector dxs(double s, void** args)
{
	//data
	math::vector dxs(2);
	const double e = *(double*) args[0];
	//path
	dxs[1] = -M_PI * sin(M_PI * s);
	dxs[0] = e * M_PI * cos(M_PI * s);
	//return
	return dxs;
}

int main(int argc, char** argv)
{
	// //application
	// QApplication application(argc, argv);
	// //window
	// Window window;
	// window.show();
	// //start
	// application.exec();
	//data
	double a = 0.10;
	double e = 0.00;
	unsigned n = 100;
	Stability stability;
	void* args[] = {&a};
	void* path_args[] = {&e};
	//stability
	stability.m_args = args;
	stability.load_example(0);
	for(unsigned i = 0; i <= n; i++)
	{
		e = 1.30 * double(i) / n;
		printf("%+.6e %+.6e\n", e, stability.maximum_energy(xs, dxs, path_args));
	}
	//return
	return EXIT_SUCCESS;
}