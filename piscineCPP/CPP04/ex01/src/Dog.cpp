#include "Dog.hpp"

Dog::Dog(void): Animal()
{
	this->type = "Dog";
	this->brain = new Brain();
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
	delete brain;
	std::cout << "Dog destructor called." << std::endl;
	return ;
}

Dog &Dog::operator=(Dog const &rhs)
{
	if (this == &rhs)
		return (*this);
	this->type = rhs.type;
	if (this->brain)
		delete this->brain;
	this->brain = new Brain();
	for (size_t i = 0; i < 100; i++)
		this->brain->ideas[i] = rhs.brain->ideas[i];
	return (*this);
}

void Dog::makeSound(void) const
{
	std::cout << "Wooof !" << std::endl;
}

void Dog::setIdea(int const index, std::string const idea)
{
	this->brain->ideas[index] = idea;
}