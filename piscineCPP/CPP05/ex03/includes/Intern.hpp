#pragma once
#include "AForm.hpp"

class Intern
{
	public:
		Intern(void);
		Intern(Intern const &rhs);
		~Intern(void);

		Intern &operator=(Intern const &rhs);

		AForm *makeForm(std::string const &name, std::string const &target);

		class FormDoesNotExistException: public std::exception
		{
			public:
				virtual const char *what(void) const throw();
		};

	private:
		AForm *_makeShrub(std::string const &target);
		AForm *_makeRobot(std::string const &target);
		AForm *_makePresident(std::string const &target);
};