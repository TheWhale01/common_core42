#ifndef __HUMAN_B_HPP__
# define __HUMAN_B_HPP__

#include "Weapon.hpp"

class HumanB {
	public:
		HumanB(std::string const name);
		~HumanB(void);

		void attack(void) const;
		void setWeapon(Weapon &weapon);
	private:
		std::string _name;
		Weapon *weapon;
};

#endif
