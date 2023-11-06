#include "irc.hpp"

NickNameInUseException::NickNameInUseException(std::string const &servername, std::string const &nickname, std::string const &cmd)
{
	_cmd = cmd;
	_nickname = nickname;
	_servername = servername;
	_error_msg = new std::string();
}

NickNameInUseException::~NickNameInUseException(void) throw() {delete _error_msg;}

const char *NickNameInUseException::what(void) const throw()
{
	*_error_msg = *_error_msg + ":" + (_servername.empty() ? "localhost" : _servername) + " "
		+ ERR_NICKNAMEINUSE + " " + (_nickname.empty() ? "*" : _nickname) + " " + _cmd + " :Nickname is already in use\r\n";
	
	return (_error_msg->c_str());
}