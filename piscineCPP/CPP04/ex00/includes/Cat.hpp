#ifndef __CAT_HPP__
# define __CAT_HPP__

#include "Animal.hpp"

class Cat: public Animal
{
	public:
		Cat(void);
		Cat(Cat const &rhs);
		~Cat(void);

		Cat &operator=(Cat const &rhs);

		void makeSound(void) const;
};

class WrongCat: public WrongAnimal
{
	public:
		WrongCat(void);
		WrongCat(WrongCat const &rhs);
		~WrongCat(void);

		WrongCat &operator=(WrongCat const &rhs);

		void makeSound(void) const;
};

#endif