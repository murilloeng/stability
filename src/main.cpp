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
	double a = 0.5;
	Stability stability;
	std::vector<math::vector> xp;
	//stability
	void* args[] = {&a};
	stability.m_args = args;
	stability.load_example(1);
	stability.path_search(xp);
	for(const math::vector& x : xp)
	{
		for(unsigned i = 0; i < x.rows(); i++)
		{
			printf("%+.2e ", x[i]);
		}
		printf("%+.2e\n", stability.m_energy(x, args));
	}
	//return
	return EXIT_SUCCESS;
}