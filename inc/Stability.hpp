#pragma once

//std
#include <vector>

//math
#include "Math/inc/linear/vector.hpp"

typedef math::vector(*path)(double, void**);

class Stability
{
public:
	//constructor
	Stability(void);

	//destructor
	~Stability(void);

	//examples
	void load_example(unsigned);

	//optimization
	double maximum_energy(path, path, void**);
	void path_search(std::vector<math::vector>&);

	//data
	void** m_args;
	math::vector m_x1;
	math::vector m_x2;
	double m_tolerance;
	unsigned m_step_max;
	unsigned m_iteration_max;
	double(*m_energy)(const math::vector&, void**);
	math::vector(*m_force)(const math::vector&, void**);
	math::matrix(*m_stiffness)(const math::vector&, void**);
};