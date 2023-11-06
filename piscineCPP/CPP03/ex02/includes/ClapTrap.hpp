#ifndef __CLAP_TRAP_HPP__
# define __CLAP_TRAP_HPP__

#include <iostream>

class ClapTrap
{
	public:
		ClapTrap(void);
		virtual ~ClapTrap(void);
		ClapTrap(std::string const &name);
		ClapTrap(ClapTrap const &to_copy);

		ClapTrap &operator=(ClapTrap const &rhs);

		virtual void attack(std::string const &target);
		void takeDamage(unsigned int amount);
		void beRepaired(unsigned int amount);
		void print_info(void) const;

	protected:
		unsigned int _hit_points;
		unsigned int _energy_points;
		unsigned int _attack_damage;
		std::string _name;
};

#endif
