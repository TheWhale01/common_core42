#ifndef __DIAMOND_TRAP_HPP__
# define __DIAMOND_TRAP_HPP__

#include "ScavTrap.hpp"
#include "FragTrap.hpp"

class DiamondTrap: public ScavTrap, public FragTrap
{
	public:
		DiamondTrap(void);
		DiamondTrap(std::string const &name);
		DiamondTrap(DiamondTrap const &rhs);
		~DiamondTrap(void);

		DiamondTrap &operator=(DiamondTrap const &rhs);

		void whoAmI(void) const;
		using ScavTrap::attack;

	private:
		std::string _name;
};

#endif