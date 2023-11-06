#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat(void):_grade(150), _name("default")
{
	return ;
}

Bureaucrat::Bureaucrat(Bureaucrat const &rhs): _name(rhs._name)
{
	*this = rhs;
	return ;
}

Bureaucrat::Bureaucrat(std::string const &name, int grade): _name(name)
{
	if (grade <= 0)
		throw (Bureaucrat::GradeTooHighException());
	else if (grade > 150)
		throw (Bureaucrat::GradeTooLowException());
	this->_grade = grade;
	return ;
}

Bureaucrat::~Bureaucrat(void)
{
	return ;
}

const char *Bureaucrat::GradeTooHighException::what(void) const throw()
{
	return ("Grade too high");
}

const char *Bureaucrat::GradeTooLowException::what(void) const throw()
{
	return ("Grade too low");
}

Bureaucrat &Bureaucrat::operator=(Bureaucrat const &rhs)
{
	if (this == &rhs)
		return (*this);
	this->_grade = rhs._grade;
	return (*this);
}

int const &Bureaucrat::getGrade(void) const
{
	return (this->_grade);
}

std::string const &Bureaucrat::getName(void) const
{
	return (this->_name);
}

void Bureaucrat::upgrade(void)
{
	try
	{
		if (this->_grade == 1)
			throw Bureaucrat::GradeTooHighException();
		this->_grade--;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Could not upgrade: " << e.what() << std::endl;
	}
}

void Bureaucrat::downgrade(void)
{
	try
	{
		if (this->_grade == 150)
			throw Bureaucrat::GradeTooLowException();
		this->_grade++;
	}
	catch (std::exception const &e)
	{
		std::cerr << "Could not downgrade: " << e.what() << std::endl;
	}
}

std::ostream &operator<<(std::ostream &stream, Bureaucrat const &bureaucrat)
{
	stream << bureaucrat.getName() << ", bureaucrat grade " << bureaucrat.getGrade() << ".";
	return (stream); 
}