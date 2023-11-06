#include "sed.hpp"

int main(int ac, char **av)
{
	if (ac != 4)
	{
		std::cerr << "Error: " << av[0] << " `filename' `to_search' `to_replace'" << std::endl;
		return (0);
	}
	std::string filename(av[1]);
	std::string to_search(av[2]);
	std::string to_replace(av[3]);
	sed(filename, to_search, to_replace);
	return (0);
}
