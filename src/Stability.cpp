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
	return (x1 * x1 - 1) * (x1 * x1 - 1);
}
static math::vector example_1_force(const math::vector& x, void** args)
{
	//data
	math::vector f(1);
	const double x1 = x[0];
	//force
	f[1] = 4 * (x1 * x1 - 1) * x1;
	///return
	return f;
}
static math::matrix example_1_stiffness(const math::vector& x, void** args)
{
	//data
	math::matrix K(1, 1);
	const double x1 = x[0];
	//stiffness
	K[0 + 1 * 0] = 4 * (3 * x1 * x1 - 1);
	//return
	return K;
}

static double example_2_energy(const math::vector& x, void** args)
{
	const double x1 = x[0];
	const double x2 = x[1];
	const double a = *(double*) args[0];
	return (x1 * x1 + x2 * x2 - 1) * (x1 * x1 + x2 * x2 - 1) + 2 * a * a * x1 * x1;
}
static math::vector example_2_force(const math::vector& x, void** args)
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
static math::matrix example_2_stiffness(const math::vector& x, void** args)
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
Stability::Stability(void) : m_tolerance(1.00e-5), m_step_max(100), m_iteration_max(100)
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
	//data
	const math::vector x1[] = {{-1}, {0, -1}};
	const math::vector x2[] = {{+1}, {0, +1}};
	double(*energy[])(const math::vector&, void**) = {
		example_1_energy, example_2_energy
	};
	math::vector(*force[])(const math::vector&, void**) = {
		example_1_force, example_2_force
	};
	math::matrix(*stiffness[])(const math::vector&, void**) = {
		example_1_stiffness, example_2_stiffness
	};
	//size
	m_x1.resize(x1[index].rows());
	m_x2.resize(x2[index].rows());
	//setup
	m_x1 = x1[index];
	m_x2 = x2[index];
	m_force = force[index];
	m_energy = energy[index];
	m_stiffness = stiffness[index];
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
void Stability::path_search(std::vector<math::vector>& x)
{
	//data
	double l;
	const unsigned nd = m_x1.rows();
	math::matrix K(nd, nd), S(nd + 1, nd + 1);
	math::vector xr(nd), f(nd), r(nd + 1), dx(nd + 1);
	//search
	x.resize(m_step_max + 1);
	x[0].resize(nd); x[0] = m_x1;
	x[m_step_max].resize(nd); x[m_step_max] = m_x2;
	for(unsigned step = 1; step < m_step_max; step++)
	{
		l = 0;
		x[step].resize(nd);
		x[step] = xr = m_x1 + double(step) / m_step_max * (m_x2 - m_x1);
		for(unsigned iteration = 0; iteration < m_iteration_max; iteration++)
		{
			//state
			f = m_force(x[step], m_args);
			K = m_stiffness(x[step], m_args);
			r[nd] = math::vector(x[step] - xr).inner(m_x2 - m_x1);
			for(unsigned i = 0; i < nd; i++) r[i] = f[i] + l * (m_x2[i] - m_x1[i]);
			//check
			if(r.norm() < m_tolerance) break;
			//tangent
			S[nd + (nd + 1) * nd] = 0;
			for(unsigned i = 0; i < nd; i++)
			{
				for(unsigned j = 0; j < nd; j++)
				{
					S[i + (nd + 1) * j] = K[i + nd * j];
				}
				S[nd + (nd + 1) * i] = S[i + (nd + 1) * nd] = m_x2[i] - m_x1[i];
			}
			S.solve(dx, r);
			//update
			l -= dx[nd];
			for(unsigned i = 0; i < nd; i++) x[step][i] -= dx[i];
		}
	}
}