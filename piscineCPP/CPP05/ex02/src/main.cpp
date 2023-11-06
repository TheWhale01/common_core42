#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "PresidentialPardonForm.hpp"

int main(void)
{
	Bureaucrat michel("michel", 1);
	Bureaucrat patrick("Patrick", 150);
	ShrubberyCreationForm shrub_form("Garden");
	RobotomyRequestForm robot_form("Robot");
	PresidentialPardonForm president_form("President");

	patrick.executeForm(robot_form);
	patrick.executeForm(shrub_form);
	patrick.executeForm(president_form);

	std::cout << std::endl;

	shrub_form.beSigned(michel);
	robot_form.beSigned(michel);
	president_form.beSigned(michel);
	
	patrick.executeForm(shrub_form);
	patrick.executeForm(robot_form);
	patrick.executeForm(president_form);

	std::cout << std::endl;

	michel.executeForm(shrub_form);
	michel.executeForm(robot_form);
	michel.executeForm(president_form);
	return (0);
}