#include "FragTrap.hpp"

int main(void)
{
	FragTrap clap("Michel");

	clap.print_info();
	clap.takeDamage(5);
	clap.print_info();
	clap.beRepaired(2);
	clap.attack("Patrick");
	clap.print_info();
	clap.highFivesGuys();
	clap.takeDamage(100);
	return (0);
}
