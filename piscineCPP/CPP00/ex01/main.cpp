#include <iostream>
#include <string.h>
#include "phonebook.hpp"

int main(void)
{
	PhoneBook phonebook;
	std::string entry;

	std::cout << "Welcome to the PhoneBook !\nPlease type (ADD, SEARCH, EXIT)\n" << std::endl;
	while (1)
	{
		std::cout << "PhoneBook> ";
		if (!std::getline(std::cin, entry).good())
			break;
		if (!entry.compare("EXIT"))
			return (0);
		else if (!entry.compare("ADD"))
			phonebook.add();
		else if (!entry.compare("SEARCH"))
			phonebook.search();
	}
	return (0);
}