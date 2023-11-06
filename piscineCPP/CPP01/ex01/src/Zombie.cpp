#include "Zombie.hpp"

Zombie::Zombie(void)
{
	return ;
}

Zombie::Zombie(std::string const &name): _name(name)
{
	return ;
}

Zombie::~Zombie(void)
{
	std::cout << this->_name << ": died." << std::endl;
	return ;
}

void Zombie::announce(void)
{
	std::cout << this->_name << ": BraiiiiiinnnzzzzZ..." << std::endl;
}

void Zombie::setName(std::string name)
{
	this->_name = name;
}
