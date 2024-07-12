//std
#include <cmath>

//math
#include "Math/inc/solvers/bisection.hpp"

//stability
#include "stability/inc/Stability.hpp"

//bisection
static double path_force(double s, void** args)
{
	//data
	path xs = (path) args[1];
	path dxs = (path) args[2];
	void** path_args = (void**) args[3];
	Stability* stability = (Stability*) args[0];
	//return
	return stability->m_force(xs(s, path_args), stability->m_args).inner(dxs(s, path_args));
}

//examples
static double example_1_energy(const math::vector& x, void** args)
{
	const double x1 = x[0];
	const double x2 = x[1];
	const double a = *(double*) args[0];
	return (x1 * x1 + x2 * x2 - 1) * (x1 * x1 + x2 * x2 - 1) + 2 * a * a * x1 * x1;
}
static math::vector example_1_force(const math::vector& x, void** args)
{
	//data
	math::vector f(2);
	const double x1 = x[0];
	const double x2 = x[1];
	const double a = *(double*) args[0];
	//force
	f[1] = 4 * (x1 * x1 + x2 * x2 - 1) * x2;
	f[0] = 4 * (x1 * x1 + x2 * x2 - 1 + a * a) * x1;
	///return
	return f;
}
static math::matrix example_1_stiffness(const math::vector& x, void** args)
{
	//data
	math::matrix K(2, 2);
	const double x1 = x[0];
	const double x2 = x[1];
	const double a = *(double*) args[0];
	//stiffness
	K[0 + 2 * 1] = K[1 + 2 * 0] = 8 * x1 * x2;
	K[1 + 2 * 1] = 4 * (x1 * x1 + 3 * x2 * x2 - 1);
	K[0 + 2 * 0] = 4 * (3 * x1 * x1 + x2 * x2 - 1 + a * a);
	//return
	return K;
}

//constructor
Stability::Stability(void)
{
	return;
}

//destructor
Stability::~Stability(void)
{
	return;
}

//examples
void Stability::load_example(unsigned index)
{
	if(index == 0)
	{
		m_force = example_1_force;
		m_energy = example_1_energy;
		m_stiffness = example_1_stiffness;
	}
}

//optimization
double Stability::maximum_energy(path xs, path dxs, void** path_args)
{
	//data
	math::bisection solver;
	double s1, s2, fs1, fs2;
	const unsigned np = 100;
	std::vector<math::vector> critical_points;
	void* solver_args[] = {this, xs, dxs, path_args};
	//search
	solver.m_system = path_force;
	for(unsigned i = 0; i < np; i++)
	{
		//force
		s1 = double(i + 0) / np;
		s2 = double(i + 1) / np;
		fs1 = m_force(xs(s1, path_args), m_args).inner(dxs(s1, path_args));
		fs2 = m_force(xs(s2, path_args), m_args).inner(dxs(s2, path_args));
		//solve
		if(fs1 * fs2 <= 0)
		{
			solver.m_x1 = s1;
			solver.m_x2 = s2;
			solver.solve(solver_args);
			critical_points.push_back(xs(solver.m_xs, path_args));
		}
	}
	//energy
	double U = 0;
	for(const math::vector& xc : critical_points)
	{
		U = fmax(U, m_energy(xc, m_args));
	}
	return U;
}