#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm(void): AForm(5, 25, "Presidential Form")
{
	this->target = "President";
	return ;
}

PresidentialPardonForm::PresidentialPardonForm(std::string const &target): AForm(5, 25, "Presidential Form")
{
	this->target = target;
	return ;
}

PresidentialPardonForm::PresidentialPardonForm(PresidentialPardonForm const &rhs): AForm(rhs)
{
	this->target = rhs.target;
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
	std::cout << this->target << " had been pardon by Zaphod Beeblebrox." << std::endl;
}