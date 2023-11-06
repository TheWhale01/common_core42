#include "irc.hpp"

NoSuchNickException::NoSuchNickException(std::string const &servername, std::string const &nickname, std::string const &cmd)
{
	_cmd = cmd;
	_nickname = nickname;
	_servername = servername;
	_error_msg = new std::string();
}

NoSuchNickException::~NoSuchNickException(void) throw() {delete _error_msg;}

const char *NoSuchNickException::what(void) const throw()
{
	*_error_msg = *_error_msg + ":" + (_servername.empty() ? "localhost" : _servername) + " "
		+ ERR_NOSUCHNICK + " " + (_nickname.empty() ? "*" : _nickname) + " " + _cmd + " :No such nick/channel\r\n";
	
	return (_error_msg->c_str());
}