#ifndef __FRAG_TRAP_HPP__
# define __FRAG_TRAP_HPP__

#include "ClapTrap.hpp"

class FragTrap: virtual public ClapTrap
{
	public:
		FragTrap(void);
		FragTrap(FragTrap const &rhs);
		FragTrap(std::string const &name);
		virtual ~FragTrap(void);

		FragTrap &operator=(FragTrap const &rhs);

		void highFivesGuys(void);
};

#endif