#include "irc.hpp"

NoTextToSendException::NoTextToSendException(std::string const &servername, std::string const &nickname)
{
	_nickname = nickname;
	_servername = servername;
	_error_msg = new std::string();
}

NoTextToSendException::~NoTextToSendException(void) throw() {delete _error_msg;}

const char *NoTextToSendException::what(void) const throw()
{
	*_error_msg = *_error_msg + ":" + (_servername.empty() ? "localhost" : _servername) + " "
		+ ERR_CANNOTSENDTOCHAN + " " + (_nickname.empty() ? "*" : _nickname) + " :No text to send\r\n";
	
	return (_error_msg->c_str());
}