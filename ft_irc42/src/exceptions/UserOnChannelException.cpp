#include "irc.hpp"

UserOnChannelException::UserOnChannelException(std::string const &servername, std::string const &nickname, std::string const &cmd, std::string const &user)
{
	_cmd = cmd;
	_user = user;
	_nickname = nickname;
	_servername = servername;
	_error_msg = new std::string();
}

UserOnChannelException::~UserOnChannelException(void) throw() {delete _error_msg;}

const char *UserOnChannelException::what(void) const throw()
{
	*_error_msg = *_error_msg + ":" + (_servername.empty() ? "localhost" : _servername) + " "
		+ ERR_USERONCHANNEL + " " + (_nickname.empty() ? "*" : _nickname) + " " + _cmd + " " + _user + " :is already on channel\r\n";
	
	return (_error_msg->c_str());
}