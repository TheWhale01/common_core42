#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(void): AForm(137, 145, "Shrubbery Form")
{
	this->target = "default_shrubbery";
	return ;
}

ShrubberyCreationForm::ShrubberyCreationForm(std::string const &target): AForm(137, 145, "Shrubbery Form")
{
	this->target = target + "_shrubbery";
	return ;
}

ShrubberyCreationForm::ShrubberyCreationForm(ShrubberyCreationForm const &rhs): AForm(rhs)
{
	*this = rhs;
	return ;
}

ShrubberyCreationForm::~ShrubberyCreationForm(void)
{
	return ;
}

/* OPERATOR OVERLOADS */

ShrubberyCreationForm &ShrubberyCreationForm::operator=(ShrubberyCreationForm const &rhs)
{
	(void)rhs;
	return (*this);	
}

/* MEMBERS FUNCTIONS */

void ShrubberyCreationForm::useForm(void) const
{
	std::ofstream outfile;

	outfile.open(this->target.c_str());
	if (!outfile.good())
		throw (ShrubberyCreationForm::AForm::FileNotOpenedException());
	outfile << "              v .   ._, |_  .," << std::endl;
    outfile << "       \'-._\\/  .  \\ /    |/_" << std::endl;
    outfile << "           \\\\  _\\, y | \\//" << std::endl;
    outfile << "     _\\_.___\\\\, \\\\/ -.\\||" << std::endl;
    outfile << "       \'7-,--.\'._||  / / ," << std::endl;
    outfile << "       /\'     \'-.\'./ / |/_.\'" << std::endl;
    outfile << "                 |    |//" << std::endl;
    outfile << "                 |_    /   " << this->target << std::endl;
    outfile << "                 |-   |" << std::endl;
    outfile << "                 |   =|" << std::endl;
    outfile << "                 |    |" << std::endl;
	outfile << "----------------/ ,  . \\--------._" << std::endl;
	outfile.close();
}