#include "Materias.hpp"
#include "MateriaSource.hpp"

MateriaSource::MateriaSource(void): _index(0)
{
	return ;
}

MateriaSource::MateriaSource(MateriaSource const &rhs)
{
	*this = rhs;
	return ;
}

MateriaSource::~MateriaSource(void)
{
	for (int i = 0; i < this->_index; i++)
		delete this->_tmp[i];
	return ;
}

MateriaSource &MateriaSource::operator=(MateriaSource const &rhs)
{
	if (this == &rhs)
		return (*this);
	for (int i = 0; i < rhs._index; i++)
	{
		delete this->_tmp[i];
		if (rhs._tmp[i]->getType() == "ice")
			this->_tmp[i] = new Ice();
		else
			this->_tmp[i] = new Cure();
	}
	this->_index = rhs._index;
	return (*this);
}

void MateriaSource::learnMateria(AMateria *m)
{
	if (!m)
		return ;
	if (this->_index == 4)
	{
		delete m;
		return ;
	}
	for (int i = 0; i < this->_index; i++)
	{
		if (this->_tmp[i]->getType() == m->getType())
		{
			delete m;
			return ;
		}
	}
	this->_tmp[this->_index++] = m;
}

AMateria *MateriaSource::createMateria(std::string const &type)
{
	bool create;

	create = false;
	for (int i = 0; i < this->_index; i++)
		if (this->_tmp[i]->getType() == type)
			create =  true;
	if (!create)
		return (NULL);
	if (type == "ice")
		return (new Ice());
	else if (type == "cure")
		return (new Cure());
	return (NULL);
}