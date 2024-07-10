#pragma once

//std
#include <vector>

//stability
#include "stability/inc/Point.hpp"
#include "stability/inc/Polynomial.hpp"

class Stability
{
public:
	//constructor
	Stability(void);

	//destructor
	~Stability(void);

private:
	//data
	Polynomial m_polynpmials[2];
	std::vector<Point> m_points;
};