#include "Span.hpp"

int main(void)
{
	Span spAdd = Span(5);
	Span spIter = Span(5);
	Span spRange = Span(10000);
	std::list<int> lst;
	std::list<int> long_range;


	lst.push_back(6);
	lst.push_back(3);
	lst.push_back(17);
	lst.push_back(9);
	lst.push_back(11);

	std::cout << "Using add number member function..." << std::endl;

	spAdd.addNumber(6);
	spAdd.addNumber(3);
	spAdd.addNumber(17);
	spAdd.addNumber(9);
	spAdd.addNumber(11);
	std::cout << spAdd.shortestSpan() << std::endl;
	std::cout << spAdd.longestSpan() << std::endl << std::endl;

	std::cout << "Using iterAdd member function..." << std::endl;
	spIter.iterAdd(lst.begin(), lst.end());
	std::cout << spIter << std::endl;
	std::cout << spIter.shortestSpan() << std::endl;
	std::cout << spIter.longestSpan() << std::endl << std::endl;

	std::cout << "Testing with 10 000 numbers span..." << std::endl;
	for (size_t i = 0; i < 10000; i++)
		long_range.push_back(i);
	spRange.iterAdd(long_range.begin(), long_range.end());
	std::cout << spRange.shortestSpan() << std::endl;
	std::cout << spRange.longestSpan() << std::endl;
	return (0);
}