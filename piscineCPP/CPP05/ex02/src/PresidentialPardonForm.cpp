#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm(void): AForm(5, 25, "Presidential Form")
{
	this->_target = "President";
	return ;
}

PresidentialPardonForm::PresidentialPardonForm(std::string const &target): AForm(5, 25, "Presidential Form")
{
	this->_target = target;
	return ;
}

PresidentialPardonForm::PresidentialPardonForm(PresidentialPardonForm const &rhs): AForm(rhs)
{
	this->_target = rhs._target;
	*this = rhs;
	return ;
}

PresidentialPardonForm::~PresidentialPardonForm(void)
{
	return ;
}

/* OPERATOR OVERLOADS */

PresidentialPardonForm &PresidentialPardonForm::operator=(PresidentialPardonForm const &rhs)
{
	(void)rhs;
	return (*this);
}

/* MEMBER FUNCTIONS */

void PresidentialPardonForm::useForm(void) const
{
	std::cout << this->_target << " had been pardon by Zaphod Beeblebrox." << std::endl;
}