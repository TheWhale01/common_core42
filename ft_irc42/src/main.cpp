#include "irc.hpp"

void sigHandler(int sig_id)
{
	(void)sig_id;
	std::cout << std::endl;
	throw (KillServerException());
}

int main(int ac, char **av)
{
	if (ac != 3)
		return (1);
	Server serv(atoi(av[1]), av[2]);
	try {serv.run();}
	catch (KillServerException const &e) {return (0);}
	return (0);
}