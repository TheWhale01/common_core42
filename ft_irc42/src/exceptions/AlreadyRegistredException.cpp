#include "irc.hpp"

AlreadyRegistredException::AlreadyRegistredException(std::string const &servername, std::string const &nickname)
{
	_nickname = nickname;
	_servername = servername;
	_error_msg = new std::string();
}

AlreadyRegistredException::~AlreadyRegistredException(void) throw() {delete _error_msg;}

const char *AlreadyRegistredException::what(void) const throw()
{
	*_error_msg = *_error_msg + ":" + (_servername.empty() ? "localhost" : _servername) + " "
		+ ERR_ALREADYREGISTRED + " " + (_nickname.empty() ? "*" : _nickname) + " :You may not reregister\r\n";
	
	return (_error_msg->c_str());
}