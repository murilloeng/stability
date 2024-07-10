#pragma once

//std
#include <vector>

class Polynomial
{
public:
	//constructor
	Polynomial(void);
	Polynomial(unsigned);

	//destructor
	~Polynomial(void);

	//print
	void print(void) const;

	//order
	unsigned order(unsigned);
	unsigned order(void) const;

	//operators
	float& operator[](unsigned);
	const float& operator[](unsigned) const;
	Polynomial operator+(const Polynomial&) const;
	Polynomial operator-(const Polynomial&) const;
	Polynomial operator*(const Polynomial&) const;
	Polynomial operator/(const Polynomial&) const;

private:
	//data
	std::vector<float> m_terms;
};