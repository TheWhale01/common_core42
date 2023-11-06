#include "Cat.hpp"

Cat::Cat(void)
{
	this->type = "Cat";
	std::cout << "Cat default constructor called." << std::endl;
	return ;
}

Cat::Cat(Cat const &rhs): Animal(rhs)
{
	*this = rhs;
	std::cout << "Cat copy constructor called." << std::endl;
	return ;
}

Cat::~Cat(void)
{
	std::cout << "Cat destructor called." << std::endl;
	return ;
}

Cat &Cat::operator=(Cat const &rhs)
{
	if (this == &rhs)
		return (*this);
	this->type = rhs.type;
	return (*this);
}

void Cat::makeSound(void) const 
{
	std::cout << "Meoow !" << std::endl;
}

/* WrongCat */

WrongCat::WrongCat(void)
{
	std::cout << "WrongCat default constructor called." << std::endl;
	return ;
}

WrongCat::WrongCat(WrongCat const &rhs): WrongAnimal(rhs)
{
	*this = rhs;
	std::cout << "WrongCat copy constructor called." << std::endl;
	return ;
}

WrongCat::~WrongCat(void)
{
	std::cout << "WrongCat destructor called." << std::endl;
	return ;
}

WrongCat &WrongCat::operator=(WrongCat const &rhs)
{
	if (this == &rhs)
		return (*this);
	this->type = rhs.type;
	return (*this);
}

void WrongCat::makeSound(void) const
{
	std::cout << "Wrong meeow !" << std::endl;
}