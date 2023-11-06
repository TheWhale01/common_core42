#include "phonebook.hpp"

std::string &Contact::getFirstName(void)
{
	return (this->first_name);
}

std::string &Contact::getLastName(void)
{
	return (this->last_name);
}

std::string &Contact::getNickname(void)
{
	return (this->nickname);
}

std::string &Contact::getPhoneNumber(void)
{
	return (this->phone_number);
}

std::string &Contact::getDarkestSecret(void)
{
	return (this->darkest_secret);
}