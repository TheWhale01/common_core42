#include "Harl.hpp"

int main(int ac, char **av)
{
	Harl harl;
	std::string level;

	if (ac != 2)
		level = "";
	else
		level = av[1];
	harl.complain(level);
	return (0);
}