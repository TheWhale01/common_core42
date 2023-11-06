#include "HumanA.hpp"

HumanA::HumanA(std::string const name, Weapon &weapon): _name(name), weapon(weapon)
{
	return ;
}

HumanA::~HumanA(void)
{
	return ;
}

void HumanA::attack(void) const 
{
	std::cout << this->_name << " attacks with their " << this->weapon.getType() << std::endl;
}
