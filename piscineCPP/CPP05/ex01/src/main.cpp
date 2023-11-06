#include "Bureaucrat.hpp"

int main(void)
{
	Form form;
	Bureaucrat michel("michel", 1);
	Bureaucrat patrick("Patrick", 150);

	form.beSigned(patrick);
	patrick.signForm(form);
	std::cout << std::endl << form << std::endl << std::endl;

	form.beSigned(michel);	
	michel.signForm(form);
	std::cout << std::endl << form << std::endl;
	return (0);
}