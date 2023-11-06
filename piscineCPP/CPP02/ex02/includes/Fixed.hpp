#ifndef __FIXED_HPP__
# define __FIXED_HPP__

#include <cmath>
#include <iostream>

class Fixed
{
	public:
		Fixed(void);
		~Fixed(void);
		Fixed(int const nb);
		Fixed(float const nb);
		Fixed(Fixed const &to_copy);

		bool operator>(Fixed const &rhs) const;
		bool operator<(Fixed const &rhs) const;
		bool operator>=(Fixed const &rhs) const;
		bool operator<=(Fixed const &rhs) const;
		bool operator==(Fixed const &rhs) const;
		bool operator!=(Fixed const &rhs) const;

		Fixed operator+(Fixed const &rhs);
		Fixed operator-(Fixed const &rhs);
		Fixed operator*(Fixed const &rhs);
		Fixed operator/(Fixed const &rhs);
		Fixed operator++(int);
		Fixed operator--(int);

		Fixed &operator++(void);
		Fixed &operator--(void);
		Fixed &operator=(Fixed const &to_copy);

		int toInt(void) const;
		int getRawBits(void) const;
		float toFloat(void) const;
		void setRawBits(int const raw);
		static Fixed min(Fixed &nb1, Fixed &nb2);
		static Fixed max(Fixed &nb1, Fixed &nb2);
		static Fixed const min(Fixed const &nb1, Fixed const &nb2);
		static Fixed const max(Fixed const &nb1, Fixed const &nb2);

	private:
		int	_nb;
		static int const _bits = 8;
};

std::ostream &operator<<(std::ostream &stream, Fixed const &nb);

#endif
