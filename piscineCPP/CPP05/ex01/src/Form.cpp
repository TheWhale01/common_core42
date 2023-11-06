#include "Form.hpp"

Form::Form(void): _s_grade(30), _x_grade(30), _sign(false), _name("default")
{
	return ;
}

Form::Form(Form const &rhs): _s_grade(rhs.getSignGrade()), _x_grade(rhs.getExecGrade()),
	_sign(rhs.getSign()), _name(rhs.getName())
{
	*this = rhs;
	return ;
}

Form::Form(int x_grade, int s_grade, std::string const &name): _s_grade(s_grade), _x_grade(x_grade),
	_sign(false), _name(name)
{
	if (x_grade <= 0 || s_grade <= 0)
		throw (Form::GradeTooHighException());
	else if (x_grade > 150 || s_grade > 150)
		throw (Form::GradeTooLowException());
	return ;
}

Form::~Form(void)
{
	return ;
}

/* Operator overloads */

Form &Form::operator=(Form const &rhs)
{
	if (this == &rhs)
		return (*this);
	this->_sign = rhs._sign;
	return (*this);
}

std::ostream &operator<<(std::ostream &stream, Form const &form)
{
	stream << "Execution grade: " << form.getExecGrade() << std::endl
		<< "Sign grade: " << form.getSignGrade() << std::endl
		<< "Is signed: " << (form.getSign() ? "true" : "false") << std::endl
		<< "Form name: " << form.getName();
	return (stream);
}

/* Member function */

int const &Form::getExecGrade(void) const
{
	return (this->_x_grade);
}

int const &Form::getSignGrade(void) const
{
	return (this->_s_grade);
}

bool const &Form::getSign(void) const
{
	return (this->_sign);
}

std::string const &Form::getName(void) const
{
	return (this->_name);
}

void Form::beSigned(Bureaucrat const &bureaucrat)
{
	try
	{
		if (bureaucrat.getGrade() > this->_s_grade)
			throw (Form::GradeTooLowException());
		this->_sign = true;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Could not sign form: " << e.what() << std::endl;
	}
}

/* Exceptions */

const char *Form::GradeTooHighException::what(void) const throw()
{
	return ("Grade too high.");
}

const char *Form::GradeTooLowException::what(void) const throw()
{
	return ("Grade too low.");
}