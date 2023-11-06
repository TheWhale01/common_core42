#include "AForm.hpp"

AForm::AForm(void): _s_grade(30), _x_grade(30), _sign(false), _name("default")
{
	return ;
}

AForm::AForm(AForm const &rhs): _s_grade(rhs.getSignGrade()), _x_grade(rhs.getExecGrade()),
	_sign(rhs.getSign()), _name(rhs.getName())
{
	*this = rhs;
	return ;
}

AForm::AForm(int x_grade, int s_grade, std::string const &name): _s_grade(s_grade), _x_grade(x_grade),
	_sign(false), _name(name)
{
	if (x_grade <= 0 || s_grade <= 0)
		throw (AForm::GradeTooHighException());
	else if (x_grade > 150 || s_grade > 150)
		throw (AForm::GradeTooLowException());
	return ;
}

AForm::~AForm(void)
{
	return ;
}

/* Operator overloads */

AForm &AForm::operator=(AForm const &rhs)
{
	if (this == &rhs)
		return (*this);
	this->_sign = rhs._sign;
	this->target = rhs.target;
	return (*this);
}

std::ostream &operator<<(std::ostream &stream, AForm const &AForm)
{
	stream << "Execution grade: " << AForm.getExecGrade() << std::endl
		<< "Sign grade: " << AForm.getSignGrade() << std::endl
		<< "Is signed: " << (AForm.getSign() ? "true" : "false") << std::endl
		<< "Form name: " << AForm.getName();
	return (stream);
}

/* Member function */

int const &AForm::getExecGrade(void) const
{
	return (this->_x_grade);
}

int const &AForm::getSignGrade(void) const
{
	return (this->_s_grade);
}

void AForm::checkGrade(Bureaucrat const &bureaucrat) const
{
	if (this->_sign == false)
		throw (AForm::FormNotSignedException());
	else if (bureaucrat.getGrade() > this->_x_grade)
		throw (AForm::GradeTooLowException());
}

bool const &AForm::getSign(void) const
{
	return (this->_sign);
}

std::string const &AForm::getName(void) const
{
	return (this->_name);
}

void AForm::beSigned(Bureaucrat const &bureaucrat)
{
	try
	{
		if (bureaucrat.getGrade() > this->_s_grade)
			throw (AForm::GradeTooLowException());
		this->_sign = true;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Could not sign form: " << e.what() << std::endl;
	}
}

void AForm::execute(Bureaucrat const &executor) const
{
	this->checkGrade(executor);
	this->useForm();
}

/* Exceptions */

const char *AForm::GradeTooHighException::what(void) const throw()
{
	return ("Grade too high.");
}

const char *AForm::GradeTooLowException::what(void) const throw()
{
	return ("Grade too low.");
}

const char *AForm::FormNotSignedException::what(void) const throw()
{
	return ("Form is not signed.");
}

const char *AForm::FileNotOpenedException::what(void) const throw()
{
	return ("File could not be opened.");
}

const char *AForm::FormNotExecutedException::what(void) const throw()
{
	return ("Form has not been executed.");
}