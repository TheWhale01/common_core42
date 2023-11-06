#include "irc.hpp"

NeedMoreParamsException::NeedMoreParamsException(std::string const &servername, std::string const &nickname, std::string const &cmd)
{
	_cmd = cmd;
	_nickname = nickname;
	_servername = servername;
	_error_msg = new std::string();
}

NeedMoreParamsException::~NeedMoreParamsException(void) throw() {delete _error_msg;}

const char *NeedMoreParamsException::what(void) const throw()
{
	*_error_msg = *_error_msg + ":" + (_servername.empty() ? "localhost" : _servername) + " "
		+ ERR_NEEDMOREPARAMS + " " + (_nickname.empty() ? "*" : _nickname) + " " + _cmd
		+ " :Not enough parameters\r\n";
	
	return (_error_msg->c_str());
}