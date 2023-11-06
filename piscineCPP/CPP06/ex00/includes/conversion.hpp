#pragma once
#include <cmath>
#include <limits>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <stdexcept>

class FormatNotValidException: public std::exception
{
	virtual const char *what(void) const throw()
	{
		return ("Format not valid.");
	}
};

void get_type(std::string &str);
void checkForm(std::string &str);
