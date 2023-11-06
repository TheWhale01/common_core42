#include "ClapTrap.hpp"

ClapTrap::ClapTrap(void): _hit_points(10), _energy_points(10), _attack_damage(0), _name("default")
{
	std::cout << "ClapTrap default constructor called." << std::endl;
	return ;
}

ClapTrap::ClapTrap(std::string const &name): _hit_points(10), _energy_points(10), _attack_damage(0), _name(name)
{
	std::cout << "ClapTrap string constructor called." << std::endl;
	return ;
}

ClapTrap::ClapTrap(ClapTrap const &to_copy)
{
	*this = to_copy;
	std::cout << "ClapTrap copy constructor called." << std::endl;
	return ;
}

ClapTrap::~ClapTrap(void)
{
	std::cout << "ClapTrap destructor called." << std::endl;
	return ;
}

ClapTrap &ClapTrap::operator=(ClapTrap const &rhs)
{
	if (this == &rhs)
		return (*this);
	this->_attack_damage = rhs._attack_damage;
	this->_energy_points = rhs._energy_points;
	this->_hit_points = rhs._hit_points;
	this->_name = rhs._name;
	return (*this);
}

void ClapTrap::attack(std::string const &target)
{
	if (!this->_hit_points || !this->_energy_points)
		return ;
	this->_energy_points--;
	std::cout << this->_name << " attacks " << target << ", causing " << this->_attack_damage << " points of damage !" << std::endl;
}

void ClapTrap::takeDamage(unsigned int amount)
{
	if (!this->_hit_points || !this->_energy_points)
		return ;
	this->_attack_damage = amount;
	if (amount > this->_hit_points)
		amount = this->_hit_points;
	this->_hit_points -= amount;
	std::cout << this->_name << " took " << amount << " points of damage !" << std::endl;
}

void ClapTrap::beRepaired(unsigned int amount)
{
	if (!this->_hit_points || !this->_energy_points)
		return ;
	this->_energy_points--;
	this->_hit_points += amount;
}

void ClapTrap::print_info(void) const
{
	std::cout << "----------------" << std::endl
		<< this->_name << " has " << this->_hit_points << " hit points" << std::endl
		<< this->_energy_points << " energy points" << std::endl
		<< this->_attack_damage << " attack damage points" << std::endl
		<< "----------------" << std::endl;
	}