#ifndef __SCAV_TRAP_HPP__
# define __SCAV_TRAP_HPP__

#include "ClapTrap.hpp"

class ScavTrap: public ClapTrap
{
	public:
		ScavTrap(void);
		ScavTrap(std::string const &name);
		ScavTrap(ScavTrap const &to_copy);
		~ScavTrap(void);
		
		ScavTrap &operator=(ScavTrap const &rhs);

		void attack(std::string const &target);
		void guardGate(void) const;
};

#endif
