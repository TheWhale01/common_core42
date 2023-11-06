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

/* WrongAnimal */

WrongAnimal::WrongAnimal(void): type("")
{
	std::cout << "WrongAnimal default constructor called." << std::endl;
	return ;
}

WrongAnimal::WrongAnimal(WrongAnimal const &rhs)
{
	*this = rhs;
	std::cout << "WrongAnimal copy constructor called." << std::endl;
	return ;
}

WrongAnimal::~WrongAnimal(void)
{
	std::cout << "WrongAnimal destructor called." << std::endl;
	return ;
}

WrongAnimal &WrongAnimal::operator=(WrongAnimal const &rhs)
{
	if (this == &rhs)
		return (*this);
	this->type = rhs.type;
	return (*this);
}

void WrongAnimal::makeSound(void) const
{
	std::cout << "Random animal sound." << std::endl;
}

std::string WrongAnimal::getType(void) const
{
	return (this->type);
}