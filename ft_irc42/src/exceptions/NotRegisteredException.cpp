#include "irc.hpp"

NotRegisteredException::NotRegisteredException(std::string const &servername, std::string const &nickname, std::string const &cmd)
{
	_cmd = cmd;
	_nickname = nickname;
	_servername = servername;
	_error_msg = new std::string();
}

NotRegisteredException::~NotRegisteredException(void) throw() {delete _error_msg;}

const char *NotRegisteredException::what(void) const throw()
{
	*_error_msg = *_error_msg + ":" + (_servername.empty() ? "localhost" : _servername) + " "
		+ ERR_NOTREGISTERED + " " + (_nickname.empty() ? "*" : _nickname) + " " + _cmd + " :You have not registered\r\n";
	
	return (_error_msg->c_str());
}