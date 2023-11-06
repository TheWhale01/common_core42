#pragma once

#include <iostream>

class Brain
{
	public:
		Brain(void);
		Brain(Brain const &rhs);
		~Brain(void);

		Brain &operator=(Brain const &rhs);

		std::string ideas[100];
};