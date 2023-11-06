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

Fixed::Fixed(int const nb): _nb(nb << this->_bits)
{
	std::cout << "Int constructor called." <<  std::endl;
	return ;
}

Fixed::Fixed(float const nb): _nb((int)roundf(nb * (1 << this->_bits)))
{
	std::cout << "Float constructor called." << std::endl;
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

int Fixed::toInt(void) const
{
	return ((int)(roundf((float)this->_nb / (1 << this->_bits))));
}

int Fixed::getRawBits(void) const
{
	return (this->_nb);
}

float Fixed::toFloat(void) const
{
	return ((float)this->_nb / (1 << this->_bits));
}

void Fixed::setRawBits(int const raw)
{
	this->_nb = raw;
}

std::ostream &operator<<(std::ostream &stream, Fixed const &nb)
{
	stream << nb.toFloat();
	return (stream);
}