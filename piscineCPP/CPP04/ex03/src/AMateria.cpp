#include "AMateria.hpp"
#include "Materias.hpp"

AMateria::AMateria(void): type("default")
{
	return ;
}

AMateria::AMateria(std::string const &type): type(type)
{
	return ;
}

AMateria::~AMateria(void)
{
	return ;
}

std::string const &AMateria::getType(void) const
{
	return (this->type);
}

void AMateria::use(ICharacter &target)
{
	std::cout << "Unknown action on " << target.getName() << std::endl;
}