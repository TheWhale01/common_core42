#include "Intern.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "PresidentialPardonForm.hpp"

Intern::Intern(void)
{
	return ;
}

Intern::Intern(Intern const &rhs)
{
	*this = rhs;
	return ;
}

Intern::~Intern(void)
{
	return ;
}

/* OPERATOR OVERLOADS */

Intern &Intern::operator=(Intern const &rhs)
{
	(void)rhs;
	return (*this);
}

/* MEMBER FUNCTIONS */

AForm *Intern::_makeShrub(std::string const &target)
{
	return (new ShrubberyCreationForm(target));
}

AForm *Intern::_makeRobot(std::string const &target)
{
	return (new RobotomyRequestForm(target));
}

AForm *Intern::_makePresident(std::string const &target)
{
	return (new PresidentialPardonForm(target));
}

AForm *Intern::makeForm(std::string const &name, std::string const &target)
{
	int i;
	std::string targets[3] = {"shrubbery creation", "robotomy request", "presidential pardon"};
	AForm *(Intern::*tab[3])(std::string const&) = {&Intern::_makeShrub, &Intern::_makeRobot, &Intern::_makePresident};

	i = -1;
	while (targets[++i] != target && i < 3);
	try
	{
		if (i == 3)
			throw (Intern::FormDoesNotExistException());
		std::cout << "Intern creates " << name << std::endl;
		return ((this->*tab[i])(target));
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (NULL);
}

/* EXCEPTIONS */

const char *Intern::FormDoesNotExistException::what(void) const throw()
{
	return ("Form does not exist");
}