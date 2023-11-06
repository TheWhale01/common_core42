#pragma once
#include "AForm.hpp"
#include <cstdlib>

class RobotomyRequestForm: public AForm
{
	public:
		RobotomyRequestForm(void);
		RobotomyRequestForm(std::string const &rhs);
		RobotomyRequestForm(RobotomyRequestForm const &rhs);
		~RobotomyRequestForm(void);

		RobotomyRequestForm &operator=(RobotomyRequestForm const &rhs);

		void useForm(void) const;
	
	private:
		std::string _target;
};