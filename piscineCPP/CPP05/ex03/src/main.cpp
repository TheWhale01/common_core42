#include "Intern.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "PresidentialPardonForm.hpp"

int main(void)
{
	AForm *form1;
	AForm *form2;
	AForm *form3;
	AForm *none;
	Intern intern;

	form1 = intern.makeForm("Shrubbery", "shrubbery creation");
	form2 = intern.makeForm("Robot", "robotomy request");
	form3 = intern.makeForm("President", "presidential pardon");
	none = intern.makeForm("None", "does not exists");

	std::cout << std::endl << *form1 << std::endl << std::endl;
	std::cout << *form2 << std::endl << std::endl;
	std::cout << *form3 << std::endl << std::endl;
	std::cout << none << std::endl;

	delete form1;
	delete form2;
	delete form3;
	return (0);
}