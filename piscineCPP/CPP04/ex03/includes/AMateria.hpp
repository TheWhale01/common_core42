#pragma once
#include <iostream>
#include "Character.hpp"

class AMateria
{
	protected:
		std::string type;

	public:
		AMateria(void);
		AMateria(std::string const &type);
		virtual ~AMateria(void);
	
		std::string const &getType(void) const;

		virtual AMateria *clone() const = 0;
		virtual void use(ICharacter &target);
};