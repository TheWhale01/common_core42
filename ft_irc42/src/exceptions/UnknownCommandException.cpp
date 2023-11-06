#include "irc.hpp"

UnknownCommandException::UnknownCommandException(std::string const &servername, std::string const &nickname, std::string const &cmd)
{
	_cmd = cmd;
	_nickname = nickname;
	_servername = servername;
	_error_msg = new std::string();
}

UnknownCommandException::~UnknownCommandException(void) throw() {delete _error_msg;}

const char *UnknownCommandException::what(void) const throw()
{
	*_error_msg = *_error_msg + ":" + (_servername.empty() ? "localhost" : _servername) + " "
		+ ERR_UNKNOWNCOMMAND + " " + (_nickname.empty() ? "*" : _nickname) + " " + _cmd
		+ " :Unknown command\r\n";
	
	return (_error_msg->c_str());
}