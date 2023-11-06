#ifndef __ANIMAL_HPP__
# define __ANIMAL_HPP__

#include <iostream>

class Animal
{
	public:
		Animal(void);
		Animal(Animal const &rhs);
		virtual ~Animal(void);

		Animal &operator=(Animal const &rhs);

		virtual void makeSound(void) const;
		std::string getType(void) const;

	protected:
		std::string type;
};

class WrongAnimal
{
	public:
		WrongAnimal(void);
		WrongAnimal(WrongAnimal const &rhs);
		~WrongAnimal(void);

		WrongAnimal &operator=(WrongAnimal const &rhs);

		void makeSound(void) const;
		std::string getType(void) const;

	protected:
		std::string type;
};

#endif