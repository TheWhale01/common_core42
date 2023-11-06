#pragma once
#include "AForm.hpp"
#include <iostream>
#include <stdexcept>

class AForm;

class Bureaucrat
{
	public:
		Bureaucrat(void);
		Bureaucrat(Bureaucrat const &rhs);
		Bureaucrat(std::string const &name, int grade);
		~Bureaucrat(void);

		Bureaucrat &operator=(Bureaucrat const &rhs);

		int const &getGrade(void) const;

		void upgrade(void);
		void downgrade(void);
		void signForm(AForm const &AForm) const;
		void executeForm(AForm const &form) const;

		std::string const &getName(void) const;

		class GradeTooLowException: public std::exception
		{
			public:
				virtual const char *what(void) const throw();
		};

		class GradeTooHighException: public std::exception
		{
			public:
				virtual const char *what(void) const throw();
		};
	
	private:
		int _grade;
		std::string const _name;
};

std::ostream &operator<<(std::ostream &stream, Bureaucrat const &bureaucrat);