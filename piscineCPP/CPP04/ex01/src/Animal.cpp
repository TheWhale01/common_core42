#include "Animal.hpp"

Animal::Animal(void): type("")
{
	std::cout << "Animal default constructor called." << std::endl;
	return ;
}

Animal::Animal(Animal const &rhs)
{
	*this = rhs;
	std::cout << "Animal copy constructor called." << std::endl;
	return ;
}

Animal::~Animal(void)
{
	std::cout << "Animal destructor called." << std::endl;
	return ;
}

Animal &Animal::operator=(Animal const &rhs)
{
	this->type = rhs.type;
	return (*this);
}

void Animal::makeSound(void) const 
{
	std::cout << "Random animal sound." << std::endl;
}

std::string Animal::getType(void) const
{
	return (this->type);
}