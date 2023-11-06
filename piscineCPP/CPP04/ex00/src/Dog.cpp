#include "Dog.hpp"

Dog::Dog(void): Animal()
{
	this->type = "Dog";
	std::cout << "Dog default constructor called." << std::endl;
	return ;
}

Dog::Dog(Dog const &rhs): Animal(rhs)
{
	*this = rhs;
	std::cout << "Dog copy constructor called." << std::endl;
	return ;
}

Dog::~Dog(void)
{
	std::cout << "Dog destructor called." << std::endl;
	return ;
}

Dog &Dog::operator=(Dog const &rhs)
{
	if (this == &rhs)
		return (*this);
	this->type = rhs.type;
	return (*this);
}

void Dog::makeSound(void) const
{
	std::cout << "Wooof !" << std::endl;
}