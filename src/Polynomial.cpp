//std
#include <cmath>
#include <cstdio>

//stability
#include "stability/inc/Polynomial.hpp"

//constructor
Polynomial::Polynomial(void) : m_terms{ 1 }
{
	return;
}
Polynomial::Polynomial(unsigned order)
{
	m_terms.resize(order + 1);
}

//destructor
Polynomial::~Polynomial(void)
{
	return;
}

//print
void Polynomial::print(void) const
{
	printf("%+.2e", m_terms[0]);
	if(m_terms.size() > 1)
	{
		printf(" %c %.2e x", m_terms[1] >= 0 ? '+' : '-', fabs(m_terms[1]));
	}
	for(unsigned i = 2; i < m_terms.size(); i++)
	{
		printf(" %c %.2e x^%d", m_terms[i] >= 0 ? '+' : '-', fabs(m_terms[i]), i);
	}
	printf("\n");
}

//order
unsigned Polynomial::order(void) const
{
	return m_terms.size() - 1;
}
unsigned Polynomial::order(unsigned order)
{
	m_terms.resize(order + 1);
	return order;
}

//operators
float& Polynomial::operator[](unsigned index)
{
	return m_terms[index];
}
const float& Polynomial::operator[](unsigned index) const
{
	return m_terms[index];
}
Polynomial Polynomial::operator+(const Polynomial& p) const
{
	//data
	Polynomial result;
	const unsigned n1 = m_terms.size();
	const unsigned n2 = p.m_terms.size();
	result.m_terms.resize(std::max(n1, n2));
	//terms
	for(unsigned i = 0; i < result.m_terms.size(); i++)
	{
		result.m_terms[i] = 0;
		if(i < n1) result.m_terms[i] += m_terms[i];
		if(i < n2) result.m_terms[i] += p.m_terms[i];
	}
	//return
	return result;
}
Polynomial Polynomial::operator-(const Polynomial& p) const
{
	//data
	Polynomial result;
	const unsigned n1 = m_terms.size();
	const unsigned n2 = p.m_terms.size();
	result.m_terms.resize(std::max(n1, n2));
	//terms
	for(unsigned i = 0; i < result.m_terms.size(); i++)
	{
		result.m_terms[i] = 0;
		if(i < n1) result.m_terms[i] -= m_terms[i];
		if(i < n2) result.m_terms[i] -= p.m_terms[i];
	}
	//return
	return result;
}
Polynomial Polynomial::operator*(const Polynomial& p) const
{
	//data
	Polynomial result;
	const int n1 = m_terms.size() - 1;
	const int n2 = p.m_terms.size() - 1;
	//terms
	result.m_terms.resize(n1 + n2 + 1);
	for(int i = 0; i <= n1 + n2; i++)
	{
		result.m_terms[i] = 0;
		const int i2 = std::min(i, n1);
		const int i1 = std::max(0, i - n2);
		for(int j = i1; j <= i2; j++)
		{
			result.m_terms[i] += m_terms[j] * p.m_terms[i - j];
		}
	}
	//return
	return result;
}
Polynomial Polynomial::operator/(const Polynomial& p) const
{
	//data
	Polynomial result;
	const int n1 = m_terms.size() - 1;
	const int n2 = p.m_terms.size() - 1;
	//check
	if(n2 > n1)
	{
		fprintf(stderr, "Error; polynomial division does not result in a polynomial!\n");
		exit(EXIT_FAILURE);
	}
	//terms
	result.m_terms.resize(n1 - n2 + 1);
	for(int i = 0; i < n1 - n2 + 1; i++)
	{
		result.m_terms[n1 - n2 - i] = m_terms[n1 - i];
		for(int j = 1; j < i; j++)
		{
			result.m_terms[n1 - n2 - i] -= p.m_terms[n2 - j] * result.m_terms[n1 - n2 - i + j];
		}
		result.m_terms[n1 - n2 - i] /= p.m_terms[n2];
	}
	//return
	return result;
}