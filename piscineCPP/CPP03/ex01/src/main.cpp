#include "ScavTrap.hpp"

int main(void)
{
	ScavTrap clap("Michel");

	clap.print_info();
	clap.takeDamage(5);
	clap.print_info();
	clap.beRepaired(2);
	clap.attack("Patrick");
	clap.print_info();
	clap.guardGate();
	clap.takeDamage(100);
	return (0);
}
