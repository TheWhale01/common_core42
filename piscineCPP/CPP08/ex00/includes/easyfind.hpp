#pragma once
#include <vector>
#include <iostream>
#include <algorithm>

class NotFoundException: public std::exception
{
	public:
		virtual const char *what(void) const throw() {return ("Occurrence Not Found.");}
};

template<typename T>
int easyfind(T container, int nb)
{
	typename T::iterator it;

	it = std::find(container.begin(), container.end(), nb);
	if (it == container.end())
		throw (NotFoundException());
	return (*it);
}

template<typename T>
std::ostream &operator<<(std::ostream &stream, std::vector<T> v)
{
	std::cout << "[";
	for (typename std::vector<T>::iterator i = v.begin(); i != v.end(); i++)
		std::cout << *i << (i + 1 != v.end() ? ", " : "");
	std::cout << "]";
	return (stream);
}