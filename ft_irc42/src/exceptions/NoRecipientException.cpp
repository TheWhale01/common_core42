#include "irc.hpp"

NoRecipientException::NoRecipientException(std::string const &servername, std::string const &nickname)
{
	_nickname = nickname;
	_servername = servername;
	_error_msg = new std::string();
}

NoRecipientException::~NoRecipientException(void) throw() {delete _error_msg;}

const char *NoRecipientException::what(void) const throw()
{
	*_error_msg = *_error_msg + ":" + (_servername.empty() ? "localhost" : _servername) + " "
		+ ERR_NORECIPIENT + " " + (_nickname.empty() ? "*" : _nickname) + " :No recipient given\r\n";
	
	return (_error_msg->c_str());
}