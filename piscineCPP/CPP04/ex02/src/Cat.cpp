#include "Cat.hpp"
#include "Brain.hpp"

Cat::Cat(void)
{
	this->type = "Cat";
	this->brain = new Brain();
	std::cout << "Cat default constructor called." << std::endl;
	return ;
}

Cat::Cat(Cat const &rhs): AAnimal(rhs)
{
	*this = rhs;
	std::cout << "Cat copy constructor called." << std::endl;
	return ;
}

Cat::~Cat(void)
{
	delete this->brain;
	std::cout << "Cat destructor called." << std::endl;
	return ;
}

Cat &Cat::operator=(Cat const &rhs)
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

void Cat::makeSound(void) const 
{
	std::cout << "Meoow !" << std::endl;
}

void Cat::setIdea(int const index, std::string const idea)
{
	this->brain->ideas[index] = idea;
}

std::string Cat::getIdea(int const index) const 
{
	return (this->brain->ideas[index]);
}