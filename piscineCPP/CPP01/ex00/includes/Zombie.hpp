#ifndef __ZOMBIE_HPP__
# define __ZOMBIE_HPP__

# include <iostream>

class Zombie {
	public:
		Zombie(void);
		Zombie(std::string const &name);
		~Zombie(void);

		void announce(void);
		void setName(std::string name);
	private:
		std::string _name;
};

void randomChump(std::string name);

Zombie *newZombie(std::string name);

#endif
