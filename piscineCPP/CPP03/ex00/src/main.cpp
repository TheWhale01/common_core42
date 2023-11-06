#include "ClapTrap.hpp"

int main(void)
{
	ClapTrap clap("Michel");

	clap.print_info();
	clap.takeDamage(5);
	clap.print_info();
	clap.beRepaired(2);
	clap.attack("Patrick");
	clap.print_info();
	clap.takeDamage(100);
	return (0);
}
