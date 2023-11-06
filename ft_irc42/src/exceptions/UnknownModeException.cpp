#include "irc.hpp"

UnknownModeException::UnknownModeException(std::string const &servername, std::string const &nickname, std::string const &cmd)
{
	_cmd = cmd;
	_nickname = nickname;
	_servername = servername;
	_error_msg = new std::string();
}

UnknownModeException::~UnknownModeException(void) throw() {delete _error_msg;}

const char *UnknownModeException::what(void) const throw()
{
	*_error_msg = *_error_msg + ":" + (_servername.empty() ? "localhost" : _servername) + " "
		+ ERR_UNKNOWNMODE + " " + (_nickname.empty() ? "*" : _nickname) + " " + _cmd + " :is unknown mode char to me\r\n";
	
	return (_error_msg->c_str());
}