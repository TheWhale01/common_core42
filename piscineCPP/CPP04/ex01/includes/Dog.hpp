#ifndef __DOG_HPP__
# define __DOG_HPP__

#include "Brain.hpp"
#include "Animal.hpp"

class Dog: public Animal
{
	public:
		Dog(void);
		Dog(Dog const &rhs);
		~Dog(void);

		Dog &operator=(Dog const &rhs);

		void makeSound(void) const;
		void setIdea(int const index, std::string const idea);
	
	private:
		Brain *brain;
};

#endif