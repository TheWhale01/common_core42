#include "AAnimal.hpp"

AAnimal::AAnimal(void): type("")
{
	std::cout << "AAnimal default constructor called." << std::endl;
	return ;
}

AAnimal::AAnimal(AAnimal const &rhs)
{
	*this = rhs;
	std::cout << "AAnimal copy constructor called." << std::endl;
	return ;
}

AAnimal::~AAnimal(void)
{
	std::cout << "AAnimal destructor called." << std::endl;
	return ;
}

AAnimal &AAnimal::operator=(AAnimal const &rhs)
{
	this->type = rhs.type;
	return (*this);
}

std::string AAnimal::getType(void) const
{
	return (this->type);
}