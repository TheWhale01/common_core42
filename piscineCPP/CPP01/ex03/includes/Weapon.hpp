#ifndef __WEAPON_HPP__
# define __WEAPON_HPP__

#include <iostream>

class Weapon {
	public:
		Weapon(std::string const type );
		~Weapon(void);
		void setType(std::string const name);
		std::string const &getType(void) const;

	private:
		std::string _type;
};

#endif
