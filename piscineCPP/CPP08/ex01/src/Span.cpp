#include "Span.hpp"

Span::Span(void): _N(0) {}
Span::Span(size_t N): _N(N) {}
Span::Span(Span const &rhs): _N(rhs._N) {*this = rhs;}
Span::~Span(void) {}

Span &Span::operator=(Span const &rhs)
{
	if (this == &rhs)
		return (*this);
	this->_N = rhs._N;
	this->_data = rhs._data;
	return (*this);
}

void Span::addNumber(int n)
{
	if (this->_data.size() == this->_N)
		throw (Span::SpanFullException());
	this->_data.push_back(n);
}

int Span::shortestSpan(void) const
{
	int min;

	if (this->_data.size() <= 1 || this->_N <= 1)
		throw (Span::DistanceNotFoundException());
	min = std::numeric_limits<int>::max();
	for (size_t i = 0; i < this->_data.size(); i++)
		for (size_t j = i + 1; j < this->_data.size(); j++)
			if (min > abs(this->_data[i] - this->_data[j]))
				min = abs(this->_data[i] - this->_data[j]);
	return (min);
}

int Span::longestSpan(void) const
{
	int max;
	int min;

	if (this->_data.size() <= 1 || this->_N <= 1)
		throw (Span::DistanceNotFoundException());
	max = *max_element(this->_data.begin(), this->_data.end());
	min = *min_element(this->_data.begin(), this->_data.end());
	return (max - min);
}

std::ostream &operator<<(std::ostream &stream, Span const &sp)
{
	std::vector<int> const v = sp.getData();

	stream << "[";
	for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); it++)
		stream << *it << (it + 1 != v.end() ? ", " : "");
	stream << "]";
	return (stream);
}