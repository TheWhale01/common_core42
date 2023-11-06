#include "irc.hpp"

NoNickNameGivenException::NoNickNameGivenException(std::string const &servername, std::string const &nickname)
{
	_nickname = nickname;
	_servername = servername;
	_error_msg = new std::string();
}

NoNickNameGivenException::~NoNickNameGivenException(void) throw() {delete _error_msg;}

const char *NoNickNameGivenException::what(void) const throw()
{
	*_error_msg = *_error_msg + ":" + (_servername.empty() ? "localhost" : _servername) + " "
		+ ERR_NONICKNAMEGIVEN + " " + (_nickname.empty() ? "*" : _nickname) + " :No nickname given\r\n";
	
	return (_error_msg->c_str());
}