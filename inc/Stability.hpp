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

	//data
	void** m_args;
	double(*m_energy)(const math::vector&, void**);
	math::vector(*m_force)(const math::vector&, void**);
	math::matrix(*m_stiffness)(const math::vector&, void**);
};