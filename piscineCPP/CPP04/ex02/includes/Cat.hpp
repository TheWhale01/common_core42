#ifndef __CAT_HPP__
# define __CAT_HPP__

#include "Brain.hpp"
#include "AAnimal.hpp"

class Cat: public AAnimal
{
	public:
		Cat(void);
		Cat(Cat const &rhs);
		~Cat(void);

		Cat &operator=(Cat const &rhs);

		void makeSound(void) const;
		void setIdea(int const index, std::string const idea);
		std::string getIdea(int const index) const;

	private:
		Brain *brain;
};

#endif