//stability
#include "stability/inc/Point.hpp"

//constructors
Point::Point(float x1, float x2)
{
	m_data[0] = x1;
	m_data[1] = x2;
}

//destructor
Point::~Point(void)
{
	return;
}