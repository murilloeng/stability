#pragma once

//std
#include <vector>

class Polynomial
{
public:
	//constructor
	Polynomial(void);

	//destructor
	~Polynomial(void);

private:
	//data
	std::vector<float> m_terms;
};