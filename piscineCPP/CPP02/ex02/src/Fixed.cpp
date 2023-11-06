#include "Fixed.hpp"

Fixed::Fixed(void): _nb(0)
{
	return ;
}

Fixed::Fixed(Fixed const &to_copy)
{
	*this = to_copy;
	return ;
}

Fixed::Fixed(int const nb): _nb(nb << this->_bits)
{
	return ;
}

Fixed::Fixed(float const nb): _nb((int)roundf(nb * (1 << this->_bits)))
{
	return ;
}

Fixed::~Fixed(void)
{
	return ;
}

Fixed	&Fixed::operator=(Fixed const &to_copy)
{
	this->_nb = to_copy.getRawBits();
	return (*this);
}

bool Fixed::operator>(Fixed const &rhs) const
{
	return (this->_nb > rhs._nb);
}

bool Fixed::operator<(Fixed const &rhs) const
{
	return (this->_nb < rhs._nb);
}

bool Fixed::operator<=(Fixed const &rhs) const
{
	return (this->_nb <= rhs._nb);
}

bool Fixed::operator>=(Fixed const &rhs) const
{
	return (this->_nb >= rhs._nb);
}

bool Fixed::operator==(Fixed const &rhs) const
{
	return (this->_nb == rhs._nb);
}

bool Fixed::operator!=(Fixed const &rhs) const
{
	return (this->_nb != rhs._nb);
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

Fixed Fixed::min(Fixed &nb1, Fixed &nb2)
{
	if (nb1 < nb2)
		return (nb1);
	return (nb2);
}

Fixed Fixed::max(Fixed &nb1, Fixed &nb2)
{
	if (nb1 >= nb2)
		return (nb1);
	return (nb2);
}

Fixed const Fixed::min(Fixed const &nb1, Fixed const &nb2)
{
	if (nb1 <= nb2)
		return (nb1);
	return (nb2);
}

Fixed const Fixed::max(Fixed const &nb1, Fixed const &nb2)
{
	if (nb1 >= nb2)
		return (nb1);
	return (nb2);
}

std::ostream &operator<<(std::ostream &stream, Fixed const &nb)
{
	stream << nb.toFloat();
	return (stream);
}

Fixed Fixed::operator+(Fixed const &rhs)
{
	return (Fixed(this->toFloat() + rhs.toFloat()));
}

Fixed Fixed::operator-(Fixed const &rhs)
{
	return (Fixed(this->toFloat() - rhs.toFloat()));
}

Fixed Fixed::operator*(Fixed const &rhs)
{
	return (Fixed(this->toFloat() * rhs.toFloat()));
}

Fixed Fixed::operator/(Fixed const &rhs)
{
	return (Fixed(this->toFloat() / rhs.toFloat()));
}

Fixed Fixed::operator++(int)
{
	Fixed tmp(*this);

	++(*this);
	return (tmp);
}

Fixed Fixed::operator--(int)
{
	Fixed tmp(*this);

	--(*this);
	return (tmp);
}

Fixed &Fixed::operator++(void)
{
	this->_nb++;
	return (*this);
}

Fixed &Fixed::operator--(void)
{
	this->_nb--;
	return (*this);
}
