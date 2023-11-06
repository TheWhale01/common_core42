#include "Brain.hpp"

Brain::Brain(void)
{
	std::cout << "Brain default constructor called." << std::endl;
	return ;
}

Brain::Brain(Brain const &rhs)
{
	*this = rhs;
	std::cout << "Brain copy constructor called." << std::endl;
	return ;
}

Brain::~Brain(void)
{
	std::cout << "Brain destructor called." << std::endl;
	return ;
}

Brain &Brain::operator=(Brain const &rhs)
{
	if (this == &rhs)
		return (*this);
	for (int i = 0; i < 100; i++)
		this->ideas[i] = std::string(rhs.ideas[i]);
	return (*this);
}