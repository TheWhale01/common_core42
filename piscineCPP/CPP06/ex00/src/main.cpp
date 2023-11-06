#include "conversion.hpp"

int main(int ac, char **av)
{
	std::string str;

	if (ac == 1)
	{
		std::cerr << av[0] << " requires at least one argument" << std::endl;
		return (0);
	}
	str = av[1];
	get_type(str);
	return (0);
}