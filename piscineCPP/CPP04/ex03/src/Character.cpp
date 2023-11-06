#include "Materias.hpp"
#include "Character.hpp"

Character::Character(void): _name("default")
{
	for (int i = 0; i < 4; i++)
		this->_inventory[i] = NULL;
	return ;
}

Character::Character(Character const &rhs)
{
	for (int i = 0; i < this->_inv_size; i++)
		this->_inventory[i] = NULL;
	*this = rhs;
	return ;
}

Character::Character(std::string const &name): _name(name)
{
	for (int i = 0; i < 4; i++)
		this->_inventory[i] = NULL;
	return ;
}

Character::~Character(void)
{
	for (int i = 0; i < this->_inv_size; i++)
		if (this->_inventory[i])
			delete this->_inventory[i];
	return ;
}

Character &Character::operator=(Character const &rhs)
{
	if (this == &rhs)
		return (*this);
	this->_name = rhs._name;
	for (int i = 0; i < this->_inv_size; i++)
	{
		if (this->_inventory[i])
			delete this->_inventory[i];
		if (rhs._inventory[i])
			this->_inventory[i] = rhs._inventory[i]->clone();
	}
	return (*this);
}

int Character::_getNextIndex(void) const
{
	int i;

	for (i = 0; i < 4 && this->_inventory[i]; i++);
	return (i);
}

std::string const &Character::getName(void) const
{
	return (this->_name);
}

void Character::equip(AMateria *m)
{
	if (this->_getNextIndex() == this->_inv_size)
	{
		std::cout << "Inventory full." << std::endl;
		return ;
	}
	if (!m)
	{
		std::cout << "Null materia type. Can't equip." << std::endl;
		return ;
	}
	this->_inventory[this->_getNextIndex()] = m;
}

void Character::unequip(int idx)
{
	if (idx >= this->_inv_size|| idx < 0)
	{
		std::cout << "Index not in range (0, " << this->_inv_size << ")" << std::endl;
		return ;
	}

	this->_inventory[idx] = NULL;
}

void Character::use(int idx, ICharacter& target)
{
	if (idx >= this->_inv_size|| idx < 0)
	{
		std::cout << "Index not in range (0, " << this->_inv_size<< ")" << std::endl;
		return ;
	}
	if (this->_inventory[idx])
		this->_inventory[idx]->use(target);
}