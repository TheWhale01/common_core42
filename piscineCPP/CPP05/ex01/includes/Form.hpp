#pragma once
#include "Bureaucrat.hpp"
#include <iostream>
#include <stdexcept>

class Bureaucrat;

class Form
{
	public:
		Form(void);
		Form(Form const &rhs);
		Form(int x_grade, int s_grade, std::string const &name);
		~Form(void);

		Form &operator=(Form const &rhs);

		int const &getExecGrade(void) const;
		int const &getSignGrade(void) const;
	
		bool const &getSign(void) const;
	
		void beSigned(Bureaucrat const &bureaucrat);
	
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
		int const _s_grade;
		int const _x_grade;
		bool _sign;
		std::string const _name;
};

std::ostream &operator<<(std::ostream &stream, Form const &form);