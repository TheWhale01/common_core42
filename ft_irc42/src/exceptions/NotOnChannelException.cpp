#include "irc.hpp"

NotOnChannelException::NotOnChannelException(std::string const &servername, std::string const &nickname, std::string const &cmd)
{
	_cmd = cmd;
	_nickname = nickname;
	_servername = servername;
	_error_msg = new std::string();
}

NotOnChannelException::~NotOnChannelException(void) throw() {delete _error_msg;}

const char *NotOnChannelException::what(void) const throw()
{
	*_error_msg = *_error_msg + ":" + (_servername.empty() ? "localhost" : _servername) + " "
		+ ERR_NOTONCHANNEL + " " + (_nickname.empty() ? "*" : _nickname) + " " + _cmd + " :You're not on that channel\r\n";
	
	return (_error_msg->c_str());
}