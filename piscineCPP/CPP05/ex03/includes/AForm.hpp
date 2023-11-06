#pragma once
#include "Bureaucrat.hpp"
#include <fstream>
#include <iostream>
#include <stdexcept>

class Bureaucrat;

class AForm
{
	public:
		AForm(void);
		AForm(AForm const &rhs);
		AForm(int x_grade, int s_grade, std::string const &name);
		virtual ~AForm(void);

		AForm &operator=(AForm const &rhs);

		int const &getExecGrade(void) const;
		int const &getSignGrade(void) const;
	
		bool const &getSign(void) const;
	
		void beSigned(Bureaucrat const &bureaucrat);
		void checkGrade(Bureaucrat const &bureaucrat) const;

		void execute(Bureaucrat const &executor) const;
		virtual void useForm(void) const = 0;
	
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

		class FormNotSignedException: public std::exception
		{
			public:
				virtual const char *what(void) const throw();
		};

		class FileNotOpenedException: public std::exception
		{
			public:
				virtual const char *what(void) const throw();
		};

		class FormNotExecutedException: public std::exception
		{
			public:
				virtual const char *what(void) const throw();
		};

	protected:
		std::string target;

	private:
		int const _s_grade;
		int const _x_grade;
		bool _sign;
		std::string const _name;
};

std::ostream &operator<<(std::ostream &stream, AForm const &AForm);