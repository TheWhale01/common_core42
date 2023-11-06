#include "Weapon.hpp"

Weapon::Weapon(std::string const type): _type(type)
{
	return ;
}

Weapon::~Weapon(void)
{
	return ;
}

void Weapon::setType(std::string const name)
{
	this->_type = name;
}

std::string const &Weapon::getType(void) const
{
	return (this->_type);
}
