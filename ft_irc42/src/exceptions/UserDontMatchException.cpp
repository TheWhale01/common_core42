#include "irc.hpp"

UserDontMatchException::UserDontMatchException(std::string const &servername, std::string const &nickname)
{
	_nickname = nickname;
	_servername = servername;
	_error_msg = new std::string();
}

UserDontMatchException::~UserDontMatchException(void) throw() {delete _error_msg;}

const char *UserDontMatchException::what(void) const throw()
{
	*_error_msg = *_error_msg + ":" + (_servername.empty() ? "localhost" : _servername) + " "
		+ ERR_USERSDONTMATCH + " " + (_nickname.empty() ? "*" : _nickname)
		+ " :Cant change mode for other users\r\n";
	
	return (_error_msg->c_str());
}