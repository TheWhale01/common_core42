#include "FragTrap.hpp"

FragTrap::FragTrap(void): ClapTrap()
{
	this->_hit_points = 100;
	this->_energy_points= 100;
	this->_attack_damage = 30;
	std::cout << "FragTrap default constructor called." << std::endl;
	return ;
}

FragTrap::FragTrap(FragTrap const &rhs): ClapTrap()
{
	*this = rhs;
	std::cout << "FragTrap copy constructor called." << std::endl;
	return ;
}

FragTrap::FragTrap(std::string const &name): ClapTrap(name)
{
	this->_hit_points = 100;
	this->_energy_points= 100;
	this->_attack_damage = 30;
	std::cout << "FragTrap string constructor called." << std::endl;
	return ;
}

FragTrap::~FragTrap(void)
{
	std::cout << "FragTrap destructor called." << std::endl;
	return ;
}

FragTrap &FragTrap::operator=(FragTrap const &rhs)
{
	if (this == &rhs)
		return (*this);
	this->_attack_damage = rhs._attack_damage;
	this->_energy_points = rhs._energy_points;
	this->_hit_points = rhs._hit_points;
	this->_name = rhs._name;
	return (*this);
}

void FragTrap::highFivesGuys(void)
{
	std::cout << "Let's have a high five !" << std::endl;
}