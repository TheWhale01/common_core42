#include "irc.hpp"

NoSuchChannelException::NoSuchChannelException(std::string const &servername, std::string const &nickname, std::string const &cmd)
{
	_cmd = cmd;
	_nickname = nickname;
	_servername = servername;
	_error_msg = new std::string();
}

NoSuchChannelException::~NoSuchChannelException(void) throw() {delete _error_msg;}

const char *NoSuchChannelException::what(void) const throw()
{
	*_error_msg = *_error_msg + ":" + (_servername.empty() ? "localhost" : _servername) + " "
		+ ERR_NOSUCHCHANNEL + " " + (_nickname.empty() ? "*" : _nickname) + " " + _cmd + " :No such channel\r\n";
	
	return (_error_msg->c_str());
}