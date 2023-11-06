#include "irc.hpp"

CannotSendToChanException::CannotSendToChanException(std::string const &servername, std::string const &nickname, std::string const &channel)
{
	_cmd = channel;
	_nickname = nickname;
	_servername = servername;
	_error_msg = new std::string();
}

CannotSendToChanException::~CannotSendToChanException(void) throw() {delete _error_msg;}

const char *CannotSendToChanException::what(void) const throw()
{
	*_error_msg = *_error_msg + ":" + (_servername.empty() ? "localhost" : _servername) + " "
		+ ERR_CANNOTSENDTOCHAN + " " + (_nickname.empty() ? "*" : _nickname) + " " + _cmd + " :Cannot send to channel\r\n";
	
	return (_error_msg->c_str());
}