#include "irc.hpp"

ErroneusNickNameException::ErroneusNickNameException(std::string const &servername, std::string const &nickname)
{
	_nickname = nickname;
	_servername = servername;
	_error_msg = new std::string();
}

ErroneusNickNameException::~ErroneusNickNameException(void) throw() {delete _error_msg;}

const char *ErroneusNickNameException::what(void) const throw()
{
	*_error_msg = *_error_msg + ":" + (_servername.empty() ? "localhost" : _servername) + " "
		+ ERR_ERRONEUSNICKNAME + " " + (_nickname.empty() ? "*" : _nickname) + " :Erroneous nickname\r\n";
	
	return (_error_msg->c_str());
}