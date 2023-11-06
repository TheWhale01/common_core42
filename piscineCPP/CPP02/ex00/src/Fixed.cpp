#include "Fixed.hpp"

Fixed::Fixed(void): _nb(0)
{
	std::cout << "Default constructor called." << std::endl;
	return ;
}

Fixed::Fixed(Fixed const &to_copy)
{
	std::cout << "Copy constructor called." << std::endl;
	*this = to_copy;
	return ;
}

Fixed::~Fixed(void)
{
	std::cout << "Destructor called." << std::endl;
	return ;
}

Fixed	&Fixed::operator=(Fixed const &to_copy)
{
	std::cout << "Copy assignment operator called." << std::endl;
	this->_nb = to_copy.getRawBits();
	return (*this);
}

int Fixed::getRawBits(void) const
{
	std::cout << "getRawBits member function called." << std::endl;
	return (this->_nb);
}

void Fixed::setRawBits(int const raw)
{
	std::cout << "setRawBits member function called." << std::endl;
	this->_nb = raw;
}