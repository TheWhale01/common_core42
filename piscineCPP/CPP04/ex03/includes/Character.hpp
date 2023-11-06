#pragma once
#include "AMateria.hpp"

class AMateria;

class ICharacter
{
	public:
		virtual ~ICharacter() {};
		virtual std::string const & getName() const = 0;
		virtual void equip(AMateria* m) = 0;
		virtual void unequip(int idx) = 0;
		virtual void use(int idx, ICharacter& target) = 0;
};

class Character: public ICharacter
{
	private:
		static int const _inv_size = 4;
		AMateria *_inventory[_inv_size];
		std::string _name;

		int _getNextIndex(void) const;

	public:
		Character(void);
		Character(Character const &rhs);
		Character(std::string const &name);
		virtual ~Character(void);

		Character &operator=(Character const &rhs);

		std::string const & getName() const;
		void equip(AMateria* m);
		void unequip(int idx);
		void use(int idx, ICharacter& target);
};