#include "irc.hpp"

InviteOnlyChanException::InviteOnlyChanException(std::string const &servername, std::string const &nickname, std::string const &cmd)
{
	_cmd = cmd;
	_nickname = nickname;
	_servername = servername;
	_error_msg = new std::string();
}

InviteOnlyChanException::~InviteOnlyChanException(void) throw() {delete _error_msg;}

const char *InviteOnlyChanException::what(void) const throw()
{
	*_error_msg = *_error_msg + ":" + (_servername.empty() ? "localhost" : _servername) + " "
		+ ERR_INVITEONLYCHAN + " " + (_nickname.empty() ? "*" : _nickname) + " " + _cmd
		+ " :Cannot join channel (+i)\r\n";

	return (_error_msg->c_str());
}