#include "irc.hpp"

UModeUnknowFlagsException::UModeUnknowFlagsException(std::string const &servername, std::string const &nickname)
{
	_nickname = nickname;
	_servername = servername;
	_error_msg = new std::string();
}

UModeUnknowFlagsException::~UModeUnknowFlagsException(void) throw() {delete _error_msg;}

const char *UModeUnknowFlagsException::what(void) const throw()
{
	*_error_msg = *_error_msg + ":" + (_servername.empty() ? "localhost" : _servername) + " "
		+ ERR_UMODEUNKNOWNFLAG + " " + (_nickname.empty() ? "*" : _nickname)
		+ " :Unknown MODE flag\r\n";
	
	return (_error_msg->c_str());
}