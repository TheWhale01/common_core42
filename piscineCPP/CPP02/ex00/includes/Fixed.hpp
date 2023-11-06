#ifndef __FIXED_HPP__
# define __FIXED_HPP__

#include <iostream>

class Fixed
{
	public:
		Fixed(void);
		~Fixed(void);
		Fixed(Fixed const &to_copy);

		Fixed &operator=(Fixed const &to_copy);

		int getRawBits(void) const;
		void setRawBits(int const raw);

	private:
		int	_nb;
		static int const _bits = 8;
};

#endif