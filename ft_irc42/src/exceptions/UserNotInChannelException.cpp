#include "irc.hpp"

UserNotInChannelException::UserNotInChannelException(std::string const &servername, std::string const &nickname, std::string const &cmd, std::string const &user)
{
	_cmd = cmd;
	_user = user;
	_nickname = nickname;
	_servername = servername;
	_error_msg = new std::string();
}

UserNotInChannelException::~UserNotInChannelException(void) throw() {delete _error_msg;}

const char *UserNotInChannelException::what(void) const throw()
{
	*_error_msg = *_error_msg + ":" + (_servername.empty() ? "localhost" : _servername) + " "
		+ ERR_NOTONCHANNEL + " " + (_nickname.empty() ? "*" : _nickname) + " " + _cmd + " " + _user + " :They aren't on that channel\r\n";
	
	return (_error_msg->c_str());
}