#include <iomanip>
#include <cstring>
#include <stdlib.h>
#include "phonebook.hpp"

PhoneBook::PhoneBook( void )
{
	this->_nb_contacts = 0;
	return ;
}

PhoneBook::~PhoneBook( void )
{
	std::cout << "Quit PhoneBook." << std::endl;
	return ;
}

void PhoneBook::_store_contact(int mode, int index)
{
	std::string *field;
	std::string prompt;

	if (mode == 0)
	{
		field = &this->_contacts[index].getFirstName();
		prompt = "What's your first name : ";
	}
	else if (mode == 1)
	{
		field = &this->_contacts[index].getLastName();
		prompt = "What's your last name : ";
	}
	else if (mode == 2)
	{
		field = &this->_contacts[index].getNickname();
		prompt = "What's your nickname : ";
	}
	else if (mode == 3)
	{
		field = &this->_contacts[index].getPhoneNumber();
		prompt = "What's your phone number : ";
	}
	else
	{
		field = &this->_contacts[index].getDarkestSecret();
		prompt = "What's your darkest secret : ";
	}
	do {
		std::cout << prompt;
		if (!getline(std::cin, *field).good())
			exit(EXIT_SUCCESS);
		if (field->empty())
			std::cout << "Cannot leave blank fields" << std::endl;
	} while (field->empty());
}

void PhoneBook::add(void)
{
	static int	index;
	std::string line;

	if (index == 8)
		index = 0;
	for (int i = 0; i < 5; i++)
		this->_store_contact(i, index);
	index++;
	if (this->_nb_contacts < 8)
		this->_nb_contacts++;
}

void	PhoneBook::_print_info(std::string str)
{
	if (str.length() > 10)
	{
		str = str.insert(9, ".");
		str = str.substr(0, 10);
	}
	std::cout << "|" << std::setw(10) << std::setfill(' ') << str;
}

void	PhoneBook::search(void)
{
	int index;
	std::string line;

	std::cout << "|-------------------------------------------|" << std::endl;
    std::cout << "|   Index  |first name|last name | nickname |" << std::endl;
    std::cout << "|----------|----------|----------|----------|" << std::endl;
	for (int i = 0; i < this->_nb_contacts; i++)
	{
		std::cout << "|" << std::setw(10) << std::setfill(' ') << i + 1;
		this->_print_info(this->_contacts[i].getFirstName());
		this->_print_info(this->_contacts[i].getLastName());
		this->_print_info(this->_contacts[i].getNickname());
		std::cout << "|" << std::endl;
	}
	std::cout << "|-------------------------------------------|" << std::endl;
	if (!this->_nb_contacts)
		return ;
	std::cout << "Please enter an index : ";
	std::getline(std::cin, line);
	index = atoi(line.c_str());
	if (index > this->_nb_contacts || index <= 0)
	{
		std::cout << "Index not in range." << std::endl;
		return ;
	}
	std::cout << "First name : " << this->_contacts[index - 1].getFirstName() << std::endl;
	std::cout << "Last name : " << this->_contacts[index - 1].getLastName() << std::endl;	
	std::cout << "Nickname : " << this->_contacts[index - 1].getNickname() << std::endl;	
	std::cout << "Phone number : " << this->_contacts[index - 1].getPhoneNumber() << std::endl;	
	std::cout << "Darkest secret : " << this->_contacts[index - 1].getDarkestSecret() << std::endl;		
}