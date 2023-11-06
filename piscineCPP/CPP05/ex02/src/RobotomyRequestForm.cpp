#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm(void): AForm(45, 72, "default")
{
	return ;
}

RobotomyRequestForm::RobotomyRequestForm(std::string const &target): AForm(45, 72, "Robot Form")
{
	this->_target = target;
	return ;
}

RobotomyRequestForm::RobotomyRequestForm(RobotomyRequestForm const &rhs): AForm(rhs)
{
	*this = rhs;
	return ;
}

RobotomyRequestForm::~RobotomyRequestForm(void)
{
	return ;
}

/* OPERATOR OVERLOAD */

RobotomyRequestForm &RobotomyRequestForm::operator=(RobotomyRequestForm const &rhs)
{
	if (this == &rhs)
		return (*this);
	this->_target = rhs._target;
	return (*this);
}

/* MEMBER FUNCTIONS */

void RobotomyRequestForm::useForm(void) const
{
	int nb;

	srand(time(NULL));
	std::cout << "*rizZzzz BzzZz rZz*" << std::endl;
	nb = rand();
	if (nb % 2)
		std::cout << this->_target << " has been robotomized." << std::endl;
	else
		std::cout << this->_target << " has not been robotomized." << std::endl;
}