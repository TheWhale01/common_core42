#include "Zombie.hpp"

int main(void)
{
	Zombie *zb = newZombie("bonsoir");
	randomChump("bonjour");

	zb->announce();
	delete zb;
	return (0);
}
