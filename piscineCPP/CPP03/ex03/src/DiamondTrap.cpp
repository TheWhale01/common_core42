#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap(void): ClapTrap(), ScavTrap(), FragTrap(), _name("default")
{
	std::cout << "DiamondTrap default constructor called." << std::endl;
	return ;
}

DiamondTrap::DiamondTrap(DiamondTrap const &rhs): ClapTrap(rhs), ScavTrap(rhs), FragTrap(rhs)
{
	*this = rhs;
	std::cout << "DiamondTrap copy constructor called." << std::endl;
	return ;
}

DiamondTrap::DiamondTrap(std::string const &name): ClapTrap(name + "_clap_name")
{
	this->_name = name;
	this->_hit_points = FragTrap::_hit_points;
	this->_energy_points = ScavTrap::_energy_points;
	this->_attack_damage = FragTrap::_attack_damage;
	std::cout << "DiamondTrap string constructor called." << std::endl;
	return ;
}

DiamondTrap::~DiamondTrap(void)
{
	if (!this->_hit_points || !this->_energy_points)
		std::cout << this->_name << " died." << std::endl;
	std::cout << "DiamondTrap destructor called." << std::endl;
	return ;
}

DiamondTrap &DiamondTrap::operator=(DiamondTrap const &rhs)
{
	if (this == &rhs)
		return (*this);
	this->_attack_damage = rhs._attack_damage;
	this->_energy_points = rhs._energy_points;
	this->_hit_points = rhs._hit_points;
	this->_name = rhs._name;
	return (*this);
}

void DiamondTrap::whoAmI(void) const
{
	std::cout << "DiamondTrap name: " << this->_name << std::endl
		<< "ClapTrap name: " << ClapTrap::_name << std::endl;
}