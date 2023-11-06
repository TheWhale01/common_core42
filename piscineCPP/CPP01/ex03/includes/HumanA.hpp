#ifndef __HUMAN_A_HPP__
# define __HUMAN_A_HPP__

#include "Weapon.hpp"

class HumanA {
	public:
		HumanA(std::string const name, Weapon &weapon);
		~HumanA(void);

		void attack(void) const;
	private:
		std::string _name;
		Weapon &weapon;
};

#endif
